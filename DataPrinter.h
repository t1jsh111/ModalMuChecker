//
// Created by Tijs Hoeijmakers on 15/12/2021.
//

#ifndef MODALMUCHECKER_DATAPRINTER_H
#define MODALMUCHECKER_DATAPRINTER_H

#include <string>
#include <vector>
#include "Formula.h"
#include "Lts.h"

class DataPrinter {
public:
    enum AlgorithmType {Naive, Emerson};

    void printInformationSingleFormulaAndLts(const Formula& formula, const Lts& lts, AlgorithmType algorithmType);

    void printTables(std::string folderPath);
private:



    std::string getFileName(const std::string& filePath);
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    void printLines(std::vector<std::string> line1, std::vector<std::string> line2, std::vector<std::string> line3);
//    bool compareNat(const std::string& a, const std::string& b);
};


#endif //MODALMUCHECKER_DATAPRINTER_H
