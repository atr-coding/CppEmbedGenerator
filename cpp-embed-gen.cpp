#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

int main(int argc, char** argv) {
	std::filesystem::path ifile;
	std::filesystem::path ofile;
	std::string ns{ "embedded_files" }; // desired namespace

	// Verify that we at least have an input and output file.
	if (argc >= 3) {
		ifile = { argv[1] };
		ofile = { argv[2] };
	} else {
		std::cerr << "Incorrect number of arguments. Missing input and/or output file.\n";
		return -1;
	}

	// Verify that the given input file exists.
	if (!std::filesystem::exists(ifile)) {
		std::cerr << "No input file specified or the file could not be found.\n";
		return -1;
	}

	// If the given output file doesn't have an extension
	// then set it to ".h".
	if(!ofile.has_extension()) {
		ofile.replace_extension(".h");
	}

	// Check if the user wants to change the namespace.
	if (argc >= 4) {
		ns = { argv[3] };
	}

	// Read in the desired file.
	std::ifstream file(ifile, std::ios::binary);
	std::string data;
	if (file) {
		file.seekg(0, std::ios::end);
		auto fsize = file.tellg();
		file.seekg(0, std::ios::beg);
		data.resize(fsize);
		file.read(data.data(), fsize);
		file.close();
	} else {
		std::cerr << "Could not open input file.\n";
		return -1;
	}

	// Write out to header.
	std::ofstream header(ofile);
	if (header) {
		header << "#pragma once\n\nnamespace " << ns << " {\n";
		header << "\tconst unsigned long long " << ifile.stem().string() << "_size { " << data.size() << " };\n";
		header << "\tconst unsigned char " << ifile.stem().string() << "[" << data.size() << "] = {\n\t\t";
		header << std::setw(2) << std::setfill('0') << std::hex;
		std::size_t counter{ 0 };
		for (auto c = data.begin(); c != data.end() - 1; ++c) {
			header << "0x" << (unsigned int)((unsigned char)(*c)) << ",";
			if (counter >= 19) {
				header << "\n\t\t";
				counter = 0;
			} else {
				counter++;
			}
		}
		header << "0x" << (unsigned int)((unsigned char)(data.back()));
		header << "\n\t};\n}";
		header.close();
	} else {
		std::cerr << "Could not open output file.\n";
		return -1;
	}
}