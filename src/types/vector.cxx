#include "../../include/types/vector.hxx"

Vector operator+(Vector vec, const Variable& other)
{
    Vector result;

    // 2. Резервируем память для оптимизации
    result.reserve(vec.size());

    // 3. Используем константные ссылки для элементов
    for (size_t i = 0; i < vec.size(); ++i)
    {
        result.push_back(vec.get(i) + other);
    }

    return result;
}

Vector operator-(Vector vec, const Variable& other)
{
    Vector result;

    // 2. Резервируем память для оптимизации
    result.reserve(vec.size());

    // 3. Используем константные ссылки для элементов
    for (size_t i = 0; i < vec.size(); ++i)
    {
        result.push_back(vec.get(i) - other);
    }

    return result;
}