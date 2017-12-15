#ifndef NU_PARSERINI_HPP
#define NU_PARSERINI_HPP

#include <fstream>
#include <map>

#include "Prerequisites.hpp"
#include "String.hpp"

namespace nu
{

class ParserIni
{
	public:
		ParserIni();
		ParserIni(const std::string& filename);

		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename = "");
		
		void set(const std::string& value, const std::string& index, const std::string& section = "");
		std::string get(const std::string& index, const std::string& section = "");

		struct IniProperty
		{
			IniProperty(const std::string& pValue, const std::string& pIndex, const std::string& pSection = "") : key(nu::StringId::hash(pSection + ":" + pIndex)), value(pValue), index(pIndex), section(pSection), saved(false) { }

			StringId key;

			std::string value;
			std::string index;
			std::string section;

			bool saved;
		};

		IniProperty& getProperty(U32 index);
		const IniProperty& getProperty(U32 index) const;
		U32 getSize() const;

		const std::string& getFilename() const;

	private:
		std::vector<IniProperty> mValues;
		std::string mFilename;
};

} // namespace nu

#endif // NU_PARSERINI_HPP
