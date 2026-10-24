#include <string>


namespace UI
{
	enum class MenuID
	{
		None,
		Main,
		Pause,
		Solo,
		Multiplayer,
		OnlineIP,
		Options,
		Rules,
		Play_rules
	};

	enum class GameAction
	{
		None,

		StartSoloEasy,
		StartSoloMedium,
		StartSoloHard,
		StartCustomGame,

		StartLocalMultiplayer,

		Resume,
		BackToMenu,

		HostGame,
		JoinGame,

		Back,
		Quit
	};

	struct Action
	{
		MenuID menuid;
		GameAction action;
	};

	//interface d'un composant de menu
	class MenuItem
	{
	public:
		virtual ~MenuItem() = default;
		virtual std::string label() const = 0;
		virtual void onLeft();
		virtual void onRight();
		virtual Action onActivate();
	};

	class ButtonItem : public MenuItem
	{
	public:
		ButtonItem(const std::string& name, Action& action, Util::Vec2& position)
			: name(name), action(action), pos(position)
		{
		}

		Action onActivate() override
		{
			return { action.menuid, action.action };
		}

	private:
		std::string name;
		Action action;
		Util::Vec2 pos;
	};

	// represente un Item toggle qui permet d'etre activer ou non (ce que j'ai compris)
	class ToggleItem : public MenuItem
	{
	public:
		ToggleItem(std::string name, bool& value) : name(std::move(name)), value(value)
		{ }
		std::string label() const override { return name + ": " + (value ? "ON" : "OFF"); }
		void onLeft() override { value = !value; }
		void onRight() override { value = !value; }
	private:
		std::string name;
		bool& value;
	};

	// represente un champ qui peut defiler de gauche a droite avec une valeure
	// Possede une valeur min et une valeur max
	template <typename T>
	class RangeItem : public MenuItem
	{
	public:
		RangeItem(const std::string& name, T& value, T min, T max, T step)
		{
			this->name = name;
			this->value = value;
			this->min = min;
			this->max = max;
			this->step = step;
		};

		std::string label() const override;
		void onLeft() override;
		void onRight() override;
	private:
		std::string name;
		T& value;
		T min;
		T max;
		T step;
	};
}