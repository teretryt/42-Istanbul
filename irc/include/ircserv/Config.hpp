#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define op_file "op.cfg"
#define banned_file "banned.cfg"
#define except_file "exception.cfg"

class Config{
	private:
	public:
		std::fstream				fOpList;
		std::vector<std::string>	operators;
		Config();
		~Config();

		//	SET FUNCTIONS
		void	addOperator(std::string userName);
		void	removeOperator(std::string userName);

		//	BOOL FUNCTIONS
		bool	isHaveOperator(std::string userName);

		//	GET FUNCTIONS

};
