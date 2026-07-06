#include "grade_processor.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<Student> validStudents =
        readStudentsFromCsv("data/students.csv");

    if (validStudents.empty()) {
        std::cout
            << "Error: Danh sach sinh vien hop le rong.\n";

        return 1;
    }

    if (!writeReport(
            "report.txt",
            validStudents
        )) {
        std::cout
            << "Loi khi ghi file bao cao.\n";

        return 1;
    }

    std::cout
        << "Bao cao da duoc xuat ra "
        << "file report.txt thanh cong.\n";

    return 0;
}