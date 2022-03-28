//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "service.h"
#include "service.h"

SERVICE_CHELTUIELI CreateService(REPOSITORY* Repository, ValidationFunction Validation)
{
    SERVICE_CHELTUIELI service;
    /*if (service == NULL)
    {
        DestroyRepository(&Repository);
        return -1;
    }*/

    service.Repository = Repository;
    service.ValidateCheltuiala = Validation;

    return service;
}

int StoreCheltuiala(PSERVICE_CHELTUIELI Service, int Id, int NumarApartament, double Suma, char* Tip, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = '\0';
    if (Service == NULL || errors == NULL)
    {
        strcat(errors, "Storing failed!\n");
        return -1;
    }

    TElem Cheltuiala;
    /*if (CreateProdus(&Produs, Id, Tip, Producator, Model, Pret, Cantitate) != 0)
    {
        strcat(errors, "Could not create a product!\n");
        return -1;
    }*/
    Cheltuiala = CreateCheltuiala(Id, NumarApartament, Suma, Tip);

    if (Service->ValidateCheltuiala(Cheltuiala, errors) == 0)
    {
        DestroyCheltuiala(Cheltuiala);
        return -1;
    }
    if(InsertCheltuiala(Service->Repository, Cheltuiala) == -1)
    {
        DestroyCheltuiala(Cheltuiala);
        strcat(errors, "Cheltuiala with this id already exists!\n");
        return -1;
    }

    return 0;
}

int EraseCheltuiala(PSERVICE_CHELTUIELI Service, int Id, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = '\0';
    if (Service == NULL)
    {
        strcat(errors, "Erasing failed!\n");
        return -1;
    }


    if (DeleteCheltuiala(Service->Repository, Id) != 0)
    {
        strcat(errors, "Cheltuiala does not exist!\n");
        return -1;
    }

    return 0;
}

int ChangeCheltuiala(PSERVICE_CHELTUIELI Service, int Id, int NumarApartament, double Suma, char* Tip, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = '\0';
    if (Service == NULL || errors == NULL)
    {
        strcat(errors, "Modification failed!\n");
        return -1;
    }

    TElem Cheltuiala;
    if (SearchCheltuiala(Service->Repository->List, Id, &Cheltuiala) != 0)
    {
        strcat(errors, "Cheltuiala does not exist!\n");
        return -1;
    }
    Cheltuiala = CopyCheltuiala(Cheltuiala);

    if (Suma != -oo)
    {
        SetSuma((PCHELTUIALA)Cheltuiala, Suma);
    }
    else
    {
        Suma = GetSuma(Cheltuiala);
    }

    if (NumarApartament != -oo)
    {
        SetNumarApartament((PCHELTUIALA)Cheltuiala, NumarApartament);
    }
    else
    {
        NumarApartament = GetNumarApartament(Cheltuiala);
    }
    if (strcmp(Tip, "") != 0)
    {
        SetTip((PCHELTUIALA)Cheltuiala, Tip);
    }
    else
    {
        Tip = GetTip(Cheltuiala);
    }

    if (Service->ValidateCheltuiala(Cheltuiala, errors) == 0)
    {
        DestroyCheltuiala(Cheltuiala);
        return -1;
    }

    if (ModifyCheltuiala(Service->Repository, Id, NumarApartament, Suma, Tip) != 0)
    {
        DestroyCheltuiala(Cheltuiala);
        strcat(errors, "The modification failed!\n");
        return -1;
    }

    DestroyCheltuiala(Cheltuiala);

    return 0;
}

DYNAMIC_VECTOR * ViewCheltuieli(PSERVICE_CHELTUIELI Service, int Mode, int AscendingMode, char* errors)
{
    errors[0] = '\0';

    DYNAMIC_VECTOR * List = CopyList(Service->Repository->List);
    if (Mode == 0) //suma
    {
        if (AscendingMode == 0) //crescator
        {
            BubbleSort(List, compareSuma, ascendingMode);
        }
        else
        {
            BubbleSort(List, compareSuma, descendingMode);
        }
    }
    else //tip
    {
        if (AscendingMode == 0) //crescator
        {
            BubbleSort(List, compareTip, ascendingMode);
        }
        else
        {
            BubbleSort(List, compareTip, descendingMode);
        }
    }

    return List;
}

DYNAMIC_VECTOR * FilterCheltuieli(PSERVICE_CHELTUIELI Service, int NumarApartament, double Suma, char* Tip, int Mode, char* errors)
{
    errors[0] = '\0';

    DYNAMIC_VECTOR * Array = CreateList();
    int count = GetLength(Service->Repository->List);

    for (int i = 0; i < count; ++i)
    {
        TElem Cheltuiala = GetElement(Service->Repository->List, i);

        if (Mode == 0)
        {
            if (isNumber(Cheltuiala, NumarApartament))
            {
                TElem Copy = CopyCheltuiala(Cheltuiala);
                Insert(Array, Copy);
            }
        }
        else if(Mode == 1)
        {
            if (isSum(Cheltuiala, Suma))
            {
                TElem Copy = CopyCheltuiala(Cheltuiala);
                Insert(Array, Copy);
            }
        }
        else
        {
            if (isType(Cheltuiala, Tip))
            {
                TElem Copy = CopyCheltuiala(Cheltuiala);
                Insert(Array, Copy);
            }
        }
    }

    return Array;
}

int Undo(PSERVICE_CHELTUIELI Service)
{
    return UndoOperation(&(Service->Repository));
}

int DestroyService(PSERVICE_CHELTUIELI Service)
{
    /*if (DestroyRepository(&repository) != 0)
    {
        return -1;
    }*/
    DestroyRepository(Service->Repository);

    return 0;
}

static void TestCreateDestroy()
{
    SERVICE_CHELTUIELI Service;

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(DestroyService(&Service) == 0);
}

static void TestStore()
{
    TElem Cheltuiala;
    TElem Result;

    SERVICE_CHELTUIELI Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreCheltuiala(&Service, 6, 5, 200.244, "apa", NULL) == -1);
    assert(StoreCheltuiala(NULL,6, 5, 200.244, "apa", errors) == -1);
    assert(strcmp(errors, "Storing failed!\n") == 0);

    assert(StoreCheltuiala(NULL,6, 5, 200.244, "apa", NULL) == -1);

    assert(SearchCheltuiala(Service.Repository->List, 6, &Result) == -1);

    assert(StoreCheltuiala(&Service, 6, 5, 200.244, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    SearchCheltuiala(Service.Repository->List, 6, &Result);
    Cheltuiala = CreateCheltuiala(6, 5, 200.244, "apa");
    assert(CheltuialaEqual(Cheltuiala, Result) == 1);

    DestroyCheltuiala(Cheltuiala);

    assert(StoreCheltuiala(&Service, 6, 5, 200.244, "apa", errors) == -1);
    assert(strcmp(errors, "Cheltuiala with this id already exists!\n") == 0);

    assert(StoreCheltuiala(&Service, -1, -20, -3, "", errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid apartment number!\nInvalid sum!\nInvalid type!\n") == 0);

    for (int i = 0; i < 120; ++i)
    {
        assert(StoreCheltuiala(&Service, i + 10, 5, 200.244, "apa", errors) == 0);
        assert(GetLength(Service.Repository->List) == i + 2);
    }

    assert(GetLength(Service.Repository->List) == 121);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void TestErase()
{
    SERVICE_CHELTUIELI Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(EraseCheltuiala(&Service, 6, errors) == -1);
    assert(EraseCheltuiala(NULL, 6, errors) == -1);
    assert(strcmp(errors, "Erasing failed!\n") == 0);
    assert(EraseCheltuiala(&Service, 6, NULL) == -1);

    assert(StoreCheltuiala(&Service, 6, 5, 200.244, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    for (int i = 0; i < 120; ++i)
    {
        assert(StoreCheltuiala(&Service, i + 10, 5, 200.244, "apa", errors) == 0);
        assert(GetLength(Service.Repository->List) == i + 2);
    }

    for (int i = 0; i < 120; ++i)
    {
        assert(EraseCheltuiala(&Service, i + 10, errors) == 0);
        assert(GetLength(Service.Repository->List) == 121 - i - 1);
    }

    assert(GetLength(Service.Repository->List) == 1);

    TElem Cheltuiala = RemoveLast(Service.Repository->List);
    assert(GetId(Cheltuiala) == 6);
    DestroyCheltuiala(Cheltuiala);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void TestChange()
{
    SERVICE_CHELTUIELI Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreCheltuiala(&Service, 6, 5, 200.244, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    assert(ChangeCheltuiala(&Service, 7, 5, 200.244, "apa", errors) == -1);
    assert(strcmp(errors, "Cheltuiala does not exist!\n") == 0);

    assert(ChangeCheltuiala(NULL, 6, 5, 200.244, "apa", errors) == -1);
    assert(strcmp(errors, "Modification failed!\n") == 0);

    assert(ChangeCheltuiala(&Service, 6, 5, 200.244, "apa", NULL) == -1);

    assert(ChangeCheltuiala(&Service, 6, 5, -200.244, "apa", errors) == -1);
    assert(strcmp(errors, "Invalid sum!\n") == 0);
    assert(ChangeCheltuiala(&Service, 6, 5, 2100.244, "apa", errors) == 0);

    DYNAMIC_VECTOR * Array;
    Array = ViewCheltuieli(&Service, 0, 0, errors);
    assert(GetSuma(GetElement(Array, 0)) == 2100.244);
    Destroy(Array, DestroyCheltuiala);

    assert(ChangeCheltuiala(&Service, 6, 5, -oo, "apa", errors) == 0);
    Array = ViewCheltuieli(&Service, 0, 0, errors);
    assert(GetSuma(GetElement(Array, 0)) == 2100.244);
    Destroy(Array, DestroyCheltuiala);

    assert(ChangeCheltuiala(&Service, 6, -oo, 5005.43, "apa", errors) == 0);
    Array = ViewCheltuieli(&Service, 0, 0, errors);
    assert(GetSuma(GetElement(Array, 0)) == 5005.43 );
    Destroy(Array, DestroyCheltuiala);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void TestView()
{
    SERVICE_CHELTUIELI Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreCheltuiala(&Service, 6, 5, 20.04, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);


    assert(StoreCheltuiala(&Service, 7, 5, 30.04, "canal", errors) == 0);
    assert(GetLength(Service.Repository->List) == 2);

    DYNAMIC_VECTOR * Array = ViewCheltuieli(&Service, 0, 0, errors);//suma crescat0r
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);
    Destroy(Array, DestroyCheltuiala);

    Array = ViewCheltuieli(&Service, 0, 1, errors);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);
    Destroy(Array, DestroyCheltuiala);

    Array = ViewCheltuieli(&Service, 1, 0, errors);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);
    Destroy(Array, DestroyCheltuiala);

    Array = ViewCheltuieli(&Service, 1, 1, errors);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);
    Destroy(Array, DestroyCheltuiala);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void TestFilter()
{
    SERVICE_CHELTUIELI Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreCheltuiala(&Service,6, 5, 20.04, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);


    assert(StoreCheltuiala(&Service, 7, 5, 30.04, "gaz", errors) == 0);
    assert(GetLength(Service.Repository->List) == 2);


    DYNAMIC_VECTOR * Array = FilterCheltuieli(&Service, 5, 0, "", 0, errors);
    assert(GetLength(Array) == 2);
    Destroy(Array, DestroyCheltuiala);

    Array = FilterCheltuieli(&Service, 0, 30.04, 0, 1, errors);
    assert(GetLength(Array) == 1);
    Destroy(Array, DestroyCheltuiala);

    Array = FilterCheltuieli(&Service, 0, 200, 0, 1, errors);
    assert(GetLength(Array) == 0);
    Destroy(Array, DestroyCheltuiala);

    Array = FilterCheltuieli(&Service, 0, 0, "apa", 2, errors);
    assert(GetLength(Array) == 1);
    Destroy(Array, DestroyCheltuiala);

    Array = FilterCheltuieli(&Service, 0, 180, "canal", 2, errors);
    assert(GetLength(Array) == 0);
    Destroy(Array, DestroyCheltuiala);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void TestUndo()
{
    //PCHELTUIALA Result, Cheltuiala;

    SERVICE_CHELTUIELI Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateCheltuiala;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreCheltuiala(&Service, 6, 5, 20.04, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    assert(Undo(&Service) == 0);
    assert(GetLength(Service.Repository->List) == 0);
    assert(Undo(&Service) == -1);

    assert(StoreCheltuiala(&Service, 7, 8, 280.04, "apa", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    assert(EraseCheltuiala(&Service, 7, errors) == 0);
    assert(GetLength(Service.Repository->List) == 0);

    assert(Undo(&Service) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    for (int i = 0; i < 10; ++i)
    {
        assert(StoreCheltuiala(&Service, i + 10, 5, 20.04, "apa", errors) == 0);
    }
    assert(GetLength(Service.Repository->List) == 11);

    for (int i = 0; i < 10; ++i)
    {
        assert(Undo(&Service) == 0);
        assert(GetLength(Service.Repository->List) == 10 - i);
    }
/*
    DYNAMIC_VECTOR * Array;
    Array = ViewCheltuieli(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 56.12) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 4);
    Destroy(Array, DestroyCheltuiala);

    assert(ChangeCheltuiala(&Service, 6, 150, 5, errors) == 0);

    Array = ViewCheltuieli(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 150) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 5);
    Destroy(Array, DestroyCheltuiala);

    assert(Undo(&Service) == 0);

    Array = ViewCheltuieli(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 56.12) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 4);
    Destroy(Array, DestroyCheltuiala);
*/

    DestroyService(&Service);
    free(errors);
}

void TestService()
{
    TestCreateDestroy();
    TestStore();
    TestView();
    TestErase();
    TestChange();
    TestFilter();
    TestUndo();
}