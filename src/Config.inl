
Config &			Config::instance()
{
	static Config *		config;

	if (config == nullptr)
		config = new Config();

	return *config;
}

Config::Value &		Config::operator[](const std::string & key)
{
	return get(key);
}

Config::Value &		Config::get(const std::string & key)
{
	return _values[key];
}

bool	Config::has(const std::string & key) const
{
	return _values.find(key) != _values.cend();
}
