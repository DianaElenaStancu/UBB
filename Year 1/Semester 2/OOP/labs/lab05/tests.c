//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "tests.h"
#include "validator.h"
#include "infrastructure.h"
#include "repository.h"
#include "service.h"
#include "utils.h"

void RunAllTests() {
    TestDomain();
    TestValidator();
    TestInfrastructure();
    TestRepository();
    TestService();
    TestUtils();
}