#include <catch2/catch_all.hpp>

#include <core/buffer.hpp>

#include <type_traits>

using echo::core::Buffer;

using echo::core::interfaces::IBuffer;

static constexpr const char *DATA = "abcdefg";

static uint64 SIZE = 8;

struct MockBuffer : public IBuffer
{
    void allocate(const uint64 &) override
    {
    }
    void release() override
    {
    }
    operator bool() const override
    {
        return true;
    }
    uint8 *get_data() const override
    {
        return nullptr;
    }
    uint64 get_size() const override
    {
        return 0;
    }
    void set_data(uint8 *) override
    {
    }
    void set_data(uint8 *, const uint64 &) override
    {
    }
    void move_from(IBuffer &&) override
    {
    }
    std::unique_ptr<IBuffer> clone() const override
    {
        return nullptr;
    }
};

TEST_CASE("Buffer", "[buffer][memory][memory management]")
{
    SECTION("It should set the data to nullptr, when using default constructor")
    {
        auto buffer = Buffer();

        REQUIRE_FALSE(buffer.get_data());
    }

    SECTION("It should set the size to 0, when using default constructor")
    {
        auto buffer = Buffer();

        REQUIRE_FALSE(buffer.get_size());
    }

    SECTION("It should set the data to an other memory address, when using uint8* and uint64 constructor")
    {
        auto buffer = Buffer((uint8 *)DATA, SIZE);

        REQUIRE_FALSE(buffer.get_data() == (uint8 *)DATA);
    }

    SECTION("It should set the data, when using uint8* and uint64 constructor")
    {
        bool condition = true;

        auto buffer = Buffer((uint8 *)DATA, SIZE);

        auto data = buffer.get_data();

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (data[i] != ((uint8 *)DATA)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should set the size, when using uint8* and uint64 constructor")
    {
        auto buffer = Buffer((uint8 *)DATA, SIZE);

        REQUIRE(buffer.get_size() == SIZE);
    }

    SECTION("It should copy the data of the original buffer to an other memory address, when using copy constructor")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer(original);

        REQUIRE_FALSE(buffer.get_data() == original.get_data());
    }

    SECTION("It should copy the data of the original buffer, when using copy constructor")
    {
        bool condition = true;

        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer(original);

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != original.get_data()[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should copy the size of the original buffer, when using copy constructor")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer(original);

        REQUIRE(buffer.get_size() == original.get_size());
    }

    SECTION("It should set the data to 0, when using uint64 constructor")
    {
        bool condition = true;

        auto buffer = Buffer(SIZE);

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != 0)
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should set the size, when using uint64 constructor")
    {
        auto buffer = Buffer(SIZE);

        REQUIRE(buffer.get_size() == SIZE);
    }

    SECTION("It should move the data, when using move constructor")
    {
        bool condition = true;

        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer(std::move(original));

        auto data = buffer.get_data();

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (data[i] != ((uint8 *)DATA)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should move the size, when using move constructor")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer(std::move(original));

        REQUIRE(buffer.get_size() == SIZE);
    }

    SECTION("It should remove ownership from original buffer, when using move constructor")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer(std::move(original));

        REQUIRE_FALSE((bool)original);
    }

    SECTION("It should copy the data of the original buffer to an other memory address, when using copy operator")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = original;

        REQUIRE_FALSE(buffer.get_data() == original.get_data());
    }

    SECTION("It should copy the data of the original buffer, when using copy operator")
    {
        bool condition = true;

        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = original;

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != original.get_data()[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should copy the size of the original buffer, when using copy operator")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = original;

        REQUIRE(buffer.get_size() == original.get_size());
    }

    SECTION("It should move the data, when using move operator")
    {
        bool condition = true;

        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = std::move(original);

        auto data = buffer.get_data();

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (data[i] != ((uint8 *)DATA)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should move the size, when using move operator")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = std::move(original);

        REQUIRE(buffer.get_size() == SIZE);
    }

    SECTION("It should remove ownership from original buffer, when using move operator")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = std::move(original);

        REQUIRE_FALSE((bool)original);
    }

    SECTION("It should copy the data of the given buffer, when using copy")
    {
        bool condition = true;

        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer::copy(original);

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != original.get_data()[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should copy the data of the given buffer to an other memory address, when using copy")
    {
        auto original = Buffer((uint8 *)DATA, SIZE);

        auto buffer = Buffer::copy(original);

        REQUIRE_FALSE(buffer.get_data() == original.get_data());
    }

    SECTION("It should allocate when size is greater than 0, when using allocate")
    {
        bool condition = true;

        auto buffer = Buffer();

        buffer.allocate(SIZE);

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != 0)
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should not allocate when size is 0, when using allocate")
    {
        auto buffer = Buffer();

        buffer.allocate(0);

        REQUIRE_FALSE(buffer.get_data());
    }

    SECTION("It should set the data if the data is not null and the size is greater than 0, when using uint8* set_data")
    {
        bool condition = true;

        auto buffer = Buffer(SIZE);

        buffer.set_data((uint8 *)DATA);

        auto data = buffer.get_data();

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (data[i] != ((uint8 *)DATA)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should not set the data if the given data is a nullptr, when using uint8* set_data")
    {
        bool condition = true;

        auto buffer = Buffer(SIZE);

        buffer.set_data(nullptr);

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != 0)
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should not set the data if the size is 0, when using uint8* set_data")
    {
        auto buffer = Buffer(0);

        buffer.set_data((uint8 *)DATA);

        REQUIRE_FALSE(buffer.get_data());
    }

    SECTION("It should set the data when given data and size are not null, when using uint8* and uint64 set_data")
    {
        bool condition = true;

        auto buffer = Buffer();

        buffer.set_data((uint8 *)DATA, SIZE);

        auto data = buffer.get_data();

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (data[i] != ((uint8 *)DATA)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should not set the data when given data is null, when using uint8* and uint64 set_data")
    {
        auto buffer = Buffer();

        buffer.set_data(nullptr, SIZE);

        REQUIRE_FALSE(buffer.get_data());
    }

    SECTION("It should not set the data when given size is null, when using uint8* and uint64 set_data")
    {
        auto buffer = Buffer();

        buffer.set_data((uint8 *)DATA, 0);

        REQUIRE_FALSE(buffer.get_data());
    }

    SECTION("It should move the buffer if the buffer is the same type, when using move_from")
    {
        bool condition = true;

        const char *data = "baa";
        const uint64 size = 4;

        auto original = Buffer((uint8 *)data, size);

        auto buffer = Buffer((uint8 *)DATA, SIZE);

        buffer.move_from(std::move(*(IBuffer *)&original));

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != ((uint8 *)data)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should not move the buffer if the buffer is not the same type, when using move_from")
    {
        bool condition = true;

        MockBuffer mock = MockBuffer();

        auto buffer = Buffer((uint8 *)DATA, SIZE);

        buffer.move_from(std::move(mock));

        for (auto i = 0; i < buffer.get_size(); i++)
        {
            if (buffer.get_data()[i] != ((uint8 *)DATA)[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should clone the buffer, when using clone")
    {
        bool condition = true;

        auto buffer = Buffer((uint8 *)DATA, SIZE);

        auto cloned = buffer.clone();

        for (auto i = 0; i < cloned->get_size(); i++)
        {
            if (cloned->get_data()[i] != buffer.get_data()[i])
            {
                condition = false;
                break;
            }
        }

        REQUIRE(condition);
    }

    SECTION("It should return a char*, when using as<char>")
    {
        bool condition = true;

        auto buffer = Buffer((uint8 *)DATA, SIZE);

        auto data = buffer.as<char>();

        REQUIRE(std::strcmp(data, DATA) == 0);
    }

    SECTION("It should return a const char* when using as_const<char>")
    {
        auto condition = true;

        auto buffer = Buffer((uint8 *)DATA, SIZE);

        auto data = buffer.as_const<char>();

        REQUIRE(std::strcmp(data, DATA) == 0);
    }
}