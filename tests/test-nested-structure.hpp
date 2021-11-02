//
// Created by rudi on 02/11/21.
//

#ifndef TEST_POINTER_STRUCTURE_HPP
#define TEST_POINTER_STRUCTURE_HPP

#include <simple-buffer.hpp>

#define NAME_LENGTH 30

namespace {
class NestedStructureTest : public ::testing::Test {
protected:
    typedef struct occupation_t {
        char dept_name[NAME_LENGTH];
        int employee_code;
    } Occupation;

    typedef struct person_t {
        char name[NAME_LENGTH];
        int age;
        Occupation *occupation;
        int weight;
    } Person;

    SimpleRPC::SimpleBuffer buffer {};

    void serializedOccupation(Occupation *occupation, SimpleRPC::SimpleBuffer *buffer)
    {
        if (!occupation) {
            buffer->Serialize((char *) SENTINEL_VALUE, sizeof(occupation));
            return;
        }

        buffer->Serialize((char *) occupation->dept_name, sizeof(char) * NAME_LENGTH);
        buffer->Serialize((char *) &occupation->employee_code, sizeof(int));
    }

    void deserializedOccupation(Occupation *occupation, SimpleRPC::SimpleBuffer *buffer)
    {
        buffer->Deserialize((char *) occupation->dept_name, sizeof(char) * NAME_LENGTH);
        buffer->Deserialize((char *) &occupation->employee_code, sizeof(int));
    }

    void serializedPerson(Person *person, SimpleRPC::SimpleBuffer *buffer)
    {
        if (!person) {
            buffer->Serialize((char *) SENTINEL_VALUE, sizeof(person));
            return;
        }

        buffer->Serialize((char *) person->name, sizeof(char) * NAME_LENGTH);
        buffer->Serialize((char *) &person->age, sizeof(int));
        serializedOccupation(person->occupation, buffer);
        buffer->Serialize((char *) &person->weight, sizeof(int));

        buffer->SeekToZero();
    }

    void deSerializePerson(Person *person, SimpleRPC::SimpleBuffer *buffer)
    {
        buffer->Deserialize(person->name, sizeof(char) * NAME_LENGTH);
        buffer->Deserialize((char *) &person->age, sizeof(int));

        Occupation *occupation = (Occupation *)malloc(sizeof(Occupation));
        person->occupation = occupation;

        deserializedOccupation(person->occupation, buffer);
        buffer->Deserialize((char *) &person->weight, sizeof(int));
    }
};
};

TEST_F(NestedStructureTest, SerializedPerson)
{
    Person personSrc, personDest;

    memset(&personSrc, 0, sizeof(personSrc));
    memset(&personDest, 0, sizeof(personDest));

    strcpy(personSrc.name, "David Andrew");
    personSrc.age = 30;
    personSrc.weight = 65;

    serializedPerson(&personSrc, &buffer);
    deSerializePerson(&personDest, &buffer);

    ASSERT_EQ(strcmp(personDest.name, personSrc.name), 0);
    ASSERT_EQ(personDest.age, 30);
    ASSERT_EQ(personDest.weight, 65);
}

#endif // TEST_POINTER_STRUCTURE_HPP
