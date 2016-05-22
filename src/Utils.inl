
std::string		__formatString(const char * formatStr, va_list args)
{
	std::string		format(formatStr);
	std::string		out;
	size_t			occurence;
	size_t			offset = 0;

	while ((occurence = format.find('$', offset)) != std::string::npos)
	{
		out.append(format, offset, occurence - offset);
		out.append(va_arg(args, char *));
		offset += occurence - offset + 1;
	}

	out.append(format, offset, std::string::npos);

	return out;
}
