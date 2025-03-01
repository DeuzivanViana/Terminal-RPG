#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>

namespace Undefined
{
	const std::string
		NAME = "UNDEFINED_NAME",
		ID = "uc:undefined";
};

class Damageable
{
public:
	Damageable() noexcept
		: __damage {0}
	{}
	Damageable(const int amount) noexcept
	{
		this->setDamage(amount);
	}

	virtual void setDamage(const int amount) noexcept
	{
		this->__damage = amount;
	}
	const int &getDamage() const noexcept
	{
		return this->__damage;
	}

	virtual ~Damageable() noexcept = default;

private:
	int __damage;

};

class Living
{
public:
	Living() noexcept
		: __life {0}
	{}
	Living(const int amount) noexcept
	{
		this->setLife(amount);
	}

	virtual void setLife(const int amount) noexcept
	{
		this->__life = std::max(0, amount);
	}
	const int &getLife() const noexcept
	{
		return this->__life;
	}
	
	virtual ~Living() noexcept = default;

private:
	int __life;

};

class Identifiable
{
public:
	Identifiable() noexcept
		: __id {Undefined::ID}
	{}
	Identifiable(const std::string text) noexcept
	{
		this->setID(text);
	}

	virtual void setID(const std::string text) noexcept
	{
		this->__id = text;
	}
	const std::string &getID() const noexcept
	{
		return this->__id;
	}

	virtual ~Identifiable() = default;

private:
	std::string __id;

};

class Nameable
{
public:
	Nameable() noexcept
		: __name {Undefined::NAME}
	{}
	Nameable(const std::string text) noexcept
	{
		this->setName(text);
	}

	virtual void setName(const std::string text) noexcept
	{
		this->__name = text;
	}
	const std::string &getName() const noexcept
	{
		return this->__name;
	}

	virtual ~Nameable() = default;

private:
	std::string __name;

};

class Entity : public Nameable, public Identifiable
{
public:
	Entity() noexcept = default;
	Entity(const std::string name, const std::string id) noexcept
		: Nameable(name), Identifiable(id)
	{}

	virtual ~Entity() noexcept = default;

private:

};

class Enemy : public Entity, public Living
{
public:
	Enemy() noexcept = default;
	Enemy(const std::string name, const std::string id)
		: Entity(name, id)
	{}

	virtual ~Enemy() noexcept = default;

};

class Item : public Nameable, public Identifiable
{
public:
	Item() noexcept = default;
	Item(const std::string name, const std::string id)
		: Nameable(name), Identifiable(id)
	{}


	virtual ~Item() noexcept = default;

private:
	
};

class Weapon : public Item, public Damageable
{
public:
	Weapon() noexcept = default;
	Weapon(const std::string name, const std::string id) noexcept
		: Item(name, id)
	{}

	virtual ~Weapon() noexcept = default;

private:

};

class CombatSystem
{
public:
	CombatSystem() noexcept = default;

	static void applyDamage(Living &living, const Damageable &damageable) noexcept
	{
		living.setLife(living.getLife() - damageable.getDamage());
	}

	virtual ~CombatSystem() noexcept = default;

private:

};

class Option
{
public:
	Option() noexcept
	{}
	Option(const std::string text) noexcept
	{
		this->setLabel(text);
	}

	virtual void setLabel(const std::string text) noexcept
	{
		this->__label = text;
	}
	const std::string &getLabel() const noexcept
	{
		return this->__label;
	}

	virtual ~Option() noexcept = default;

private:
	std::string __label;

};

class Menu
{
public:
	Menu() noexcept
		: __current_option {0}
	{
	}

	virtual void addOption(const Option option) noexcept
	{
		this->__options.push_back(option);
	}
	virtual void prompt()
	{
		std::string selected_option;

		for(std::uint32_t i = 0; i < this->__options.size(); i++)
		{
			std::cout << i << " - " << this->__options[i].getLabel() << (this->__current_option == i ? " <---\n" : "\n");
		}
		
		std::cout << "action > ";
		this->__current_option = std::max<std::uint32_t>(0, std::min<std::uint32_t>(this->_tryGetLineNumber(), this->__options.size() - 1));
	}

	virtual ~Menu() noexcept = default;

protected:
	virtual const int _tryGetLineNumber()
	{
		std::string value;
		std::getline(std::cin, value);

		try
		{
			return std::stoi(value);
		}
		catch(...)
		{
			std::cerr << "Option invalid, please try again.\n";
		}

		return 0;
	}

private:
	std::vector<Option> __options;
	std::uint32_t __current_option;

};

int main(int, char*[])
{
	Menu menu;

	menu.addOption(Option("Attack"));
	menu.addOption(Option("Items"));
	menu.addOption(Option("Exit"));

	while(true)
	{
		menu.prompt();
	}

	return EXIT_SUCCESS;
}
