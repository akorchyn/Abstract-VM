bool	parseLine(std::string &line)
{
	std::string::iterator it = line.begin();

	const auto char_number_ = [](const int &attr, auto &, bool &pass) {
		pass = (attr > -129 && attr < 128);
	}; // lambda to check char limits


	//Rule to parse supported data types
	auto types = qi::raw[qi::lexeme[qi::lit("int8(") >> qi::int_[char_number_] >> qi::char_(')') |
						 	qi::lit("int16(") >> qi::short_ >> qi::char_(')')  |
						 	qi::lit("int32(") >> qi::int_ >> qi::char_(')')  |
						 	qi::lit("float(") >> qi::float_ >> qi::char_(')')  |
						 	qi::lit("double(") >> qi::double_ >> qi::char_(')') ]];

	auto comment = ';' >> *qi::char_; // Rule to parse commentary

	return qi::phrase_parse(it, line.end(),
								comment |
								("push" >> types) [boost::bind(&push, _1)] |
								"pop" >> -comment |
								"dump" >> -comment |
								"assert" >> qi::space >> types >> -comment |
								"add" >> -comment |
								"sub" >> -comment |
								"mul" >> -comment |
								"div" >> -comment |
								"mod" >> -comment |
								"print" >> -comment |
								"exit" >> -comment |
								"",
								qi::space) && it == line.end();
}