
#pragma once

#include <map>
#include <string>

class Config
{
public:
	union Value
	{
		int			i;
		unsigned	u;
		char *		s;
	};

	~Config() = delete;

	Value &			operator[](const std::string & key);

	static Config &	instance();

	void			set(const std::string & key, const Value & value);
	Value &			get(const std::string & key);
	bool			has(const std::string & key) const;

protected:
	std::map<std::string, Value>	_values;

private:
	Config() = default;
};

#include "../src/Config.inl"
