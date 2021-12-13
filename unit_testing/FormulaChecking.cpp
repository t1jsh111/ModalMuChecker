//
// Created by tijsh on 13-12-2021.
//
#include "gtest/gtest.h"
#include "Parser.h"
#include "NaiveAlgorithm.h"
#include "EmersonLeiAlgorithm.h"

class QuickTest : public testing::Test {
protected:

    void SetUp() override {
    }

    // TearDown() is invoked immediately after a test finishes.  Here we
    // check if the test was too slow.
    void TearDown() override {
    }

};


// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class BooleanTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        transitionSystem = new Lts(parser_space::Parser::parseLts("../resources/testcases/boolean/test.aut"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete transitionSystem;
    }
public:
    static Lts* transitionSystem;
};


Lts* BooleanTesting::transitionSystem = nullptr;


TEST_F(BooleanTesting, form1) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form1.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);


    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}


TEST_F(BooleanTesting, form2) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form2.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = BooleanTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form3) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form3.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form4) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form4.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form5) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form5.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = BooleanTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form6) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form6.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = BooleanTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form7) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form7.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form8) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form8.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = BooleanTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(BooleanTesting, form9) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/boolean/form9.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *BooleanTesting::transitionSystem);

    const std::unordered_set<int> expectation = BooleanTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}


// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class CombinedTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        transitionSystem = new Lts(parser_space::Parser::parseLts("../resources/testcases/combined/test.aut"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete transitionSystem;
    }
public:
    static Lts* transitionSystem;
};
Lts* CombinedTesting::transitionSystem = nullptr;

TEST_F(CombinedTesting, form1) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/combined/form1.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);

    const std::unordered_set<int> expectation = {0,1,2,4,6};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(CombinedTesting, form2) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/combined/form2.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);

    const std::unordered_set<int> expectation = {0,1,2,4,6};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(CombinedTesting, form3) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/combined/form3.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);

    const std::unordered_set<int> expectation = {0,1,2,3,4,5,6};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(CombinedTesting, form4) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/combined/form4.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);

    const std::unordered_set<int> expectation = CombinedTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(CombinedTesting, form5) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/combined/form5.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *CombinedTesting::transitionSystem);

    const std::unordered_set<int> expectation = {3,5};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}


// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class FixpointsOnlyTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        transitionSystem = new Lts(parser_space::Parser::parseLts("../resources/testcases/fixpoints_only/test.aut"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete transitionSystem;
    }
public:
    static Lts* transitionSystem;
};
Lts* FixpointsOnlyTesting::transitionSystem = nullptr;

TEST_F(FixpointsOnlyTesting, form1) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/fixpoints_only/form1.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);

    const std::unordered_set<int> expectation = FixpointsOnlyTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(FixpointsOnlyTesting, form2) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/fixpoints_only/form2.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(FixpointsOnlyTesting, form3) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/fixpoints_only/form3.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);

    const std::unordered_set<int> expectation = FixpointsOnlyTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(FixpointsOnlyTesting, form4) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/fixpoints_only/form4.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(FixpointsOnlyTesting, form5) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/fixpoints_only/form5.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *FixpointsOnlyTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}


class ModalOperatorsTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        transitionSystem = new Lts(parser_space::Parser::parseLts("../resources/testcases/modal_operators/test.aut"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete transitionSystem;
    }
public:
    static Lts* transitionSystem;
};
Lts* ModalOperatorsTesting::transitionSystem = nullptr;

TEST_F(ModalOperatorsTesting, form1) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/modal_operators/form1.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);

    const std::unordered_set<int> expectation = ModalOperatorsTesting::transitionSystem->getStates();
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(ModalOperatorsTesting, form2) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/modal_operators/form2.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);

    const std::unordered_set<int> expectation = {0,1,2,4,6};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(ModalOperatorsTesting, form3) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/modal_operators/form3.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);

    const std::unordered_set<int> expectation = {3,5,7};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(ModalOperatorsTesting, form4) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/modal_operators/form4.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);

    const std::unordered_set<int> expectation = {1,2,4};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}

TEST_F(ModalOperatorsTesting, form5) {
    auto form = parser_space::Parser::parseFormulaFile("../resources/testcases/modal_operators/form5.mcf");
    const auto& naiveSolution = NaiveAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);
    const auto& emersonSolution = EmersonLeiAlgorithm::evaluate(*form, *ModalOperatorsTesting::transitionSystem);

    const std::unordered_set<int> expectation = {};
    EXPECT_EQ(naiveSolution, expectation);
    EXPECT_EQ(emersonSolution, expectation);
}