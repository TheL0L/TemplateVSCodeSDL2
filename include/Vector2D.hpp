#pragma once

/**
 * @class Vector2D
 * @brief Represents a 2D vector.
 */
class Vector2D
{
public:
    float x; ///< The x-coordinate of the vector.
    float y; ///< The y-coordinate of the vector.

    /**
     * @brief Default constructor. Initializes the vector to (0, 0).
     */
    Vector2D();

    /**
     * @brief Parameterized constructor. Initializes the vector with specified x and y values.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    Vector2D(float x, float y);

    /**
     * @brief Copy constructor. Creates a copy of the given vector.
     * @param other The vector to copy.
     */
    Vector2D(const Vector2D& other);

    /**
     * @brief Destructor. Default implementation.
     */
    ~Vector2D() = default;

    /**
     * @brief Addition operator. Adds two vectors component-wise.
     * @param other The vector to add.
     * @return The result of the addition.
     */
    Vector2D operator+ (const Vector2D& other) const;

    /**
     * @brief Subtraction operator. Subtracts two vectors component-wise.
     * @param other The vector to subtract.
     * @return The result of the subtraction.
     */
    Vector2D operator- (const Vector2D& other) const;

    /**
     * @brief Scalar multiplication operator. Multiplies the vector by a scalar.
     * @param scalar The scalar value.
     * @return The result of the multiplication.
     */
    Vector2D operator* (float scalar) const;

    /**
     * @brief Scalar division operator. Divides the vector by a scalar.
     *
     * @note Division by zero results in undefined behavior.
     *
     * @param scalar The scalar value.
     * @return The result of the division.
     */
    Vector2D operator/ (float scalar) const;

    /**
     * @brief Equality comparison operator.
     * @param other The vector to compare.
     * @return True if the vectors are equal, false otherwise.
     */
    bool operator== (const Vector2D& other) const;

    /**
     * @brief Copy assignment operator. Assigns the value of another vector to this vector.
     * @param other The vector to copy.
     * @return Reference to the modified vector.
     */
    Vector2D& operator= (const Vector2D& other);

    /**
     * @brief Compound addition operator. Adds another vector to this vector.
     * @param other The vector to add.
     */
    void operator+= (const Vector2D& other);

    /**
     * @brief Compound subtraction operator. Subtracts another vector from this vector.
     * @param other The vector to subtract.
     */
    void operator-= (const Vector2D& other);

    /**
     * @brief Compound multiplication operator. Multiplies the vector by a scalar.
     * @param scalar The scalar value.
     */
    void operator*= (float scalar);

    /**
     * @brief Compound division operator. Divides the vector by a scalar.
     *
     * @note Division by zero results in undefined behavior.
     *
     * @param scalar The scalar value.
     */
    void operator/= (float scalar);

    /**
     * @brief Calculates the dot product of this vector with another vector.
     * @param other The other vector.
     * @return The dot product of the two vectors.
     */
    float dotProduct(const Vector2D& other) const;
};
