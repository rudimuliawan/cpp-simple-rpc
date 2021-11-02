//
// Created by rudi on 02/11/21.
//

#ifndef TEST_SIMPLE_STRUCTURE_HPP
#define TEST_SIMPLE_STRUCTURE_HPP

#include <simple-buffer.hpp>

#define NAME_LENGTH 30

namespace {
class SimpleStructureTest : public ::testing::Test {
protected:
    typedef struct person_t {
        char name[NAME_LENGTH];
        int age;
        int weight;
    } Person;

    SimpleRPC::SimpleBuffer buffer {};

    void serializedPerson(Person *person, SimpleRPC::SimpleBuffer *buffer)
    {
        if (!person) {
            buffer->Serialize((char *) SENTINEL_VALUE, sizeof(person));
            return;
        }

        buffer->Serialize((char *) person->name, sizeof(char) * NAME_LENGTH);
        buffer->Serialize((char *) &person->age, sizeof(int));
        buffer->Serialize((char *) &person->weight, sizeof(int));

        buffer->SeekToZero();
    }

    void deserializePerson(Person *person, SimpleRPC::SimpleBuffer *buffer)
    {
        buffer->Deserialize(person->name, sizeof(char) * NAME_LENGTH);
        buffer->Deserialize((char *) &person->age, sizeof(int));
        buffer->Deserialize((char *) &person->weight, sizeof(int));
    }
};
};

TEST_F(SimpleStructureTest, SerializedPerson)
{
    Person personSrc, personDest;

    memset(&personSrc, 0, sizeof(personSrc));
    memset(&personDest, 0, sizeof(personDest));

    strcpy(personSrc.name, "David Andrew");
    personSrc.age = 30;
    personSrc.weight = 65;

    serializedPerson(&personSrc, &buffer);
    deserializePerson(&personDest, &buffer);

    ASSERT_EQ(strcmp(personDest.name, personSrc.name), 0);
    ASSERT_EQ(personDest.age, 30);
    ASSERT_EQ(personDest.weight, 65);
}

#endif // TEST_SIMPLE_STRUCTURE_HPP
