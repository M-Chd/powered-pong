#include "game.h"

using namespace Util;
using namespace UI;
using namespace Network;

namespace Core
{

    void Game::init()
    {
        int width = windowRenderer.width;
        int height = windowRenderer.height;

        try
        {
            windowRenderer.init();
        }
        catch (std::runtime_error e)
        {
            printf("%s", e.what());
            return;
        }

        menuManager.init(
            windowRenderer.renderer,
            "../../../assets/fonts/IMPACT.ttf",
            50,
            WHITE
        );

        scoreboard.init(
            view,
            windowRenderer.renderer,
            "../../../assets/fonts/Beach-Ball.ttf",
            30,
            WHITE,
            { 10, 20 },
            { 1100, 20 }
        );

        if (debug)
        {
            debugOverlay.init(
                view,
                "../../../assets/fonts/Beach-Ball.ttf",
                14,
                SDL_Color{ 200, 200, 200, 255 },
                10,
                static_cast<float>(windowRenderer.height) - 20,
                10 // nombre de ligne de debug | number of debug lines
            );
        }

        connectUI.init(
            view,
            windowRenderer.renderer,
            "../../../assets/fonts/Beach-Ball.ttf",
            50,
            WHITE,
            { (float)windowRenderer.height / 2, (float)windowRenderer.width / 2 }
        );

        inputIp.init(
            windowRenderer.renderer,
            "../../../assets/fonts/IMPACT.ttf",
            40,
            WHITE,
            { static_cast<float>(MENU_DEFAULT_X), static_cast<float>(MENU_FIRST_Y - 50) }
        );

        state = GameState::MENU;
    }

    void Game::update(float dt)
    {
        if (state == GameState::PLAY)
        {
            if (inputmngr.isKeyDown(SDL_SCANCODE_ESCAPE))
            {
                state = GameState::PAUSE;
                menuManager.setCurrentMenu(MenuID::Pause);
            }
        }

        switch (state)
        {
        case GameState::PAUSE:
            updateMenu(dt);
            break;

        case GameState::MENU:
            updateMenu(dt);
            break;

        case GameState::POINT:
            updatePoint(dt);
            break;

        case GameState::PLAY:
            updatePlay(dt);
            break;

        case GameState::CONNECTING:
            updateConnecting(dt);
            break;

        default:
            break;
        }

        if (debug)
            updateDebug(dt);
    }

    void Game::updateMenu(float dt)
    {
        menuInputTimer -= dt;

        if (menuInputTimer <= 0.f)
        {
            if (inputmngr.isKeyDown(SDL_SCANCODE_UP))
            {
                menuManager.moveUp();
                menuInputTimer = MENU_REPEAT_DELAY;
            }
            else if (inputmngr.isKeyDown(SDL_SCANCODE_DOWN))
            {
                menuManager.moveDown();
                menuInputTimer = MENU_REPEAT_DELAY;
            }
            else if (inputmngr.isKeyDown(SDL_SCANCODE_RETURN))
            {
                handleMenuAction(menuManager.activate());
                menuInputTimer = MENU_REPEAT_DELAY;
            }
        }
    }

    void Game::updatePoint(float dt)
    {
        pauseTimer -= dt;

        if (pauseTimer <= 0.f)
            state = GameState::PLAY;
    }

    void Game::updatePlay(float dt)
    {
        switch (netRole)
        {
        case NetRole::Offline:
            updatePlayOffline(dt);
            break;

        case NetRole::Host:
            updatePlayHost(dt);
            break;

        case NetRole::Client:
            updatePlayClient(dt);
            break;

        default:
            break;
        }
    }

    void Game::updatePlayOffline(float dt)
    {
        PlayerInputState p1 =
            buildLocalInput(SDL_SCANCODE_W, SDL_SCANCODE_S, inputmngr);

        PlayerInputState p2 =
            buildLocalInput(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, inputmngr);

        applyMatchEvent(currentmatch.update(dt, p1, p2));
    }

    void Game::updatePlayHost(float dt)
    {
        PlayerInputState p1 =
            buildLocalInput(SDL_SCANCODE_W, SDL_SCANCODE_S, inputmngr);

        networkManager.processMessages();

        hostTickAccumulator += dt;

        const float TICK = 1.f / 30.f;

        while (hostTickAccumulator >= TICK)
        {
            PlayerInputState p2 = networkManager.getRemoteInput(2);
            MatchEvent e = currentmatch.update(TICK, p1, p2);

            networkManager.broadcastGameState(
                buildNetGameState(currentmatch)
            );

            applyMatchEvent(e);

            hostTickAccumulator -= TICK;
        }
    }

    void Game::updatePlayClient(float dt)
    {
        networkManager.processMessages();

        PlayerInputState localInput =
            (localPlayerSlot == 1)
            ? buildLocalInput(SDL_SCANCODE_W, SDL_SCANCODE_S, inputmngr)
            : buildLocalInput(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, inputmngr);

        networkManager.sendInput(localInput);

        Network::NetGameState snapshot;

        if (networkManager.pollGameState(snapshot))
            applySnapshotToMatch(snapshot);

        if (networkManager.pollMatchEnded() ||
            networkManager.getConnectionState() == Network::ConnectionState::Failed)
        {
            state = GameState::MENU;
            networkManager.teardown();
            netRole = NetRole::Offline;
        }
    }

    void Game::updateConnecting(float dt)
    {
        networkManager.processMessages();

        if (networkManager.getConnectionState() == Network::ConnectionState::Failed)
        {
            netRole = NetRole::Offline;
            state = GameState::MENU;
            return;
        }

        int slot;

        if (networkManager.pollMatchStart(slot))
        {
            localPlayerSlot = slot;
            state = GameState::PLAY;
        }
    }

    void Game::applyMatchEvent(MatchEvent e)
    {
        switch (e)
        {
        case MatchEvent::PointScored:
            scoreboard.update(
                windowRenderer.renderer,
                currentmatch.getPlayerOne().getScore(),
                currentmatch.getPlayerTwo().getScore()
            );

            pauseTimer = 1.f;
            state = GameState::POINT;
            break;

        case MatchEvent::MatchFinished:
            scoreboard.update(
                windowRenderer.renderer,
                currentmatch.getPlayerOne().getScore(),
                currentmatch.getPlayerTwo().getScore()
            );

            state = GameState::MENU;

            if (netRole != NetRole::Offline)
                networkManager.teardown();

            netRole = NetRole::Offline; // Si ajouté regle le probleme du Host qui reste en online

            menuManager.setLastCurrentMenu(); // pour une raison, ne met pas le curseur tout en haut

            break;

        default:
            break;
        }
    }

    void Game::applySnapshotToMatch(const Network::NetGameState& s)
    {
        auto x1 = currentmatch.getPlayerOne().getCenter().x;
        auto x2 = currentmatch.getPlayerTwo().getCenter().x;

        currentmatch.getBall().setPosition({ s.ballX, s.ballY });
        currentmatch.getPlayerOne().setCenter({ x1, s.p1Y });
        currentmatch.getPlayerTwo().setCenter({ x2, s.p2Y });

        if (s.p1Score != currentmatch.getPlayerOne().getScore() ||
            s.p2Score != currentmatch.getPlayerTwo().getScore())
        {
            currentmatch.getPlayerOne().setScore(s.p1Score);
            currentmatch.getPlayerTwo().setScore(s.p2Score);

            scoreboard.update(
                windowRenderer.renderer,
                s.p1Score,
                s.p2Score
            );
        }
    }

    Network::NetGameState Game::buildNetGameState(Match& match)
    {
        auto& ball = match.getBall();
        auto& p1 = match.getPlayerOne();
        auto& p2 = match.getPlayerTwo();

        Network::NetGameState state = {
            .ballX = ball.getCenter().x,
            .ballY = ball.getCenter().y,
            .ballSpeedX = ball.getSpeed().x,
            .ballSpeedY = ball.getSpeed().y,
            .p1Y = p1.getCenter().y,
            .p2Y = p2.getCenter().y,
            .p1Score = p1.getScore(),
            .p2Score = p2.getScore()
        };

        return state;
    }

    void Game::render()
    {
        SDL_SetRenderDrawColor(
            windowRenderer.renderer,
            0,
            0,
            0,
            255
        );

        SDL_RenderClear(windowRenderer.renderer);

        switch (state)
        {
        case GameState::MENU:
            renderMenu();
            break;

        case GameState::PLAY:
            renderPlay();
            break;

        case GameState::POINT:
            renderPlay();
            break;

        case GameState::PAUSE:
            renderPause();
            break;

        case GameState::CONNECTING:
            renderConnecting();
            break;

        default:
            break;
        }

        SDL_RenderPresent(windowRenderer.renderer);
    }

    void Game::renderPause()
    {
        menuManager.render(windowRenderer.renderer);
    }

    void Game::renderMenu()
    {
        menuManager.render(windowRenderer.renderer);

        if (menuManager.getCurrentMenuID() == MenuID::OnlineIP)
        {
            this->textInputActive = true;
            inputIp.render(windowRenderer.renderer);
        }
        else
        {
            this->textInputActive = false;
        }
    }

    void Game::renderPlay()
    {
        currentmatch.render(windowRenderer.renderer);

        view.drawAllUI(windowRenderer.renderer, {LayerType::ConnectLayer});
    }

    void Game::renderConnecting()
    {
        view.drawThisType(windowRenderer.renderer, LayerType::ConnectLayer);
    }

    void Game::handleMenuAction(UI::Action a)
    {
        if (a.menuid != MenuID::None)
        {
            menuManager.setCurrentMenu(a.menuid);
        }
        else if (a.action == GameAction::Resume)
        {
            state = GameState::PLAY;
        }
        else if (a.action == GameAction::BackToMenu)
        {
            state = GameState::MENU;
            menuManager.setCurrentMenu(MenuID::Main);
        }
        else
        {
            auto ip = inputIp.getIP();

            switch (a.action)
            {
            case GameAction::StartSoloEasy:
                currentmatch = Match(
                    Match::MatchSettings{
                        .type = Match::MatchType::Solo,
                        .difficulty = GameDifficulty::EASY
                    }
                );

                scoreboard.update(windowRenderer.renderer, currentmatch.getPlayerOne().getScore(),
                    currentmatch.getPlayerTwo().getScore());

                state = GameState::PLAY;
                break;

            case GameAction::StartSoloMedium:
                currentmatch = Match(
                    Match::MatchSettings{
                        .type = Match::MatchType::Solo,
                        .difficulty = GameDifficulty::MEDIUM
                    }
                );

                scoreboard.update(windowRenderer.renderer, currentmatch.getPlayerOne().getScore(),
                    currentmatch.getPlayerTwo().getScore());

                state = GameState::PLAY;
                break;

            case GameAction::StartSoloHard:
                currentmatch = Match(
                    Match::MatchSettings{
                        .type = Match::MatchType::Solo,
                        .difficulty = GameDifficulty::HARD
                    }
                );

                scoreboard.update(windowRenderer.renderer, currentmatch.getPlayerOne().getScore(),
                    currentmatch.getPlayerTwo().getScore());

                state = GameState::PLAY;
                break;

            case GameAction::StartLocalMultiplayer:
                currentmatch = Match(
                    Match::MatchSettings{
                        .type = Match::MatchType::Multi,
                        .difficulty = GameDifficulty::NONE
                    }
                );

                scoreboard.update(windowRenderer.renderer, currentmatch.getPlayerOne().getScore(),
                    currentmatch.getPlayerTwo().getScore());

                state = GameState::PLAY;
                break;

            case GameAction::HostGame:
                hostTickAccumulator = 0.f;
                netRole = NetRole::Host;
                localPlayerSlot = 1;

                networkManager.startHost(
                    networkManager.getActivePort()
                );

                networkManager.connectLocalClient();

                currentmatch = Match(
                    Match::MatchSettings{
                        .type = Match::MatchType::Multi,
                        .difficulty = GameDifficulty::NONE
                    }
                );

                scoreboard.update(windowRenderer.renderer, currentmatch.getPlayerOne().getScore(),
                    currentmatch.getPlayerTwo().getScore());

                // Need to change this for a future update, online matches are temporarily without items
                currentmatch.getRules().toggleItems();

                state = GameState::CONNECTING;
                break;

            case GameAction::JoinGame:

                if (!inputIp.isValidIP())
                {
                    printf("Adresse IP invalide : %s\n", ip.c_str());
                    break;
                }

                netRole = NetRole::Client;

                currentmatch = Match(
                    Match::MatchSettings{
                        .type = Match::MatchType::Multi
                    }
                );

                scoreboard.update(windowRenderer.renderer, currentmatch.getPlayerOne().getScore(),
                    currentmatch.getPlayerTwo().getScore());

                // Need to change this for a future update, online matches are temporarily without items
                currentmatch.getRules().toggleItems();

                networkManager.joinServer(ip.c_str(), networkManager.getActivePort());

                state = GameState::CONNECTING;
                break;

            case GameAction::Back:
                menuManager.returnBack();
                break;

            case GameAction::Quit:
                running = false;
                break;

            default:
                break;
            }
        }
    }

    void Game::handleEvent(const SDL_Event& e)
    {
        if (menuManager.getCurrentMenuID() == MenuID::OnlineIP)
        {
            if (!textInputActive)
            {
                SDL_StartTextInput();
                textInputActive = true;
            }
            inputIp.handleEvent(e);
            return;
        }
        else
        {
            if (textInputActive)
            {
                SDL_StopTextInput();
                textInputActive = false;
            }
        }
    }

    inline std::string game_state_to_string(Game::GameState& state)
    {
        switch (state)
        {
        case Game::GameState::PAUSE:
            return "Pause";

        case Game::GameState::MENU:
            return "Menu";

        case Game::GameState::POINT:
            return "Point";

        case Game::GameState::PLAY:
            return "Point";

        case Game::GameState::CONNECTING:
            return "Connecting";

        default:
            return "Unknown";
        }
    }

    inline static std::string netRole_to_string(Game::NetRole& netRole)
    {
        switch (netRole)
        {
        case Game::NetRole::Client:     return "Client";
        case Game::NetRole::Host:       return "Host";
        case Game::NetRole::Offline:    return "Offline";
        default:
            return "Unknown";
            break;
        }
    }

    void Game::updateDebug(float dt)
    {
        auto& ball = currentmatch.getBall();
        auto& p_one = currentmatch.getPlayerOne();
        auto& p_two = currentmatch.getPlayerTwo();

        int mouseX, mouseY;
        auto ballPos = ball.getCenter();
        auto p1Pos = p_one.getCenter();
        auto p2Pos = p_two.getCenter();

        SDL_GetMouseState(&mouseX, &mouseY);

        debugOverlay.update(
            windowRenderer.renderer,
            {
                "Ball pos: (" + fmt(ballPos.x) + ", " + fmt(ballPos.y) + ")",
                "Ball speed X: " + fmt(ball.getSpeed().x),
                "Ball speed Y: " + fmt(ball.getSpeed().y),
                "P1 pos: (" + fmt(p1Pos.x) + ", " + fmt(p1Pos.y) + ")",
                "P2 pos: (" + fmt(p2Pos.x) + ", " + fmt(p2Pos.y) + ")",
                "Mouse position: (" + fmt((float)mouseX) + ", " + fmt((float)mouseY) + ")",
                "State: " + game_state_to_string(state),
                "frame time: " + fmt(1.0f / static_cast<float>(dt)),
                "Current Ball effect: " +
                    Entities::effect_to_string(ball.getBallEffect()),
                "Net Role: " + netRole_to_string(netRole)
            }
        );
    }

    void Game::parseArgs(int argc, char** argv)
    {
        for (int i = 1; i < argc; i++)
		{
			if (argv[i] == "-debug")
				debug = true;
		}
    }

    void Game::quit()
    {
        view.clear();
        windowRenderer.quit();
    }

}
