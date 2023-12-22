#pragma once
#include <assert.h>
#include <ImGuiManager.h>
#define _USE_MATH_DEFINES
#include "Vector3.h"
#include "Matrix4x4.h"
#include "math.h"

Vector3 Add(const Vector3 v1, const Vector3& v2);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 Multiply2(const float& v1, const Vector3& v2);

// スケーリング行列を宣言
Matrix4x4 matScale(const Vector3 scale);

Matrix4x4 matRotX(float rotation);

Matrix4x4 matRotY(float rotation);

Matrix4x4 matRotZ(float rotation);

Matrix4x4 matRotXYZ(float rotationX, float rotationY, float rotationZ);

// 平行移動行列を宣言
Matrix4x4 matTrans(const Vector3 translation);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

Vector3 Normalize(const Vector3& v);

Matrix4x4 Transpose(const Matrix4x4& m);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateMatrix(const Vector3& radian);

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);

Vector3 Multiply(float scalar, const Vector3& v);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Vector3 Normalize2(const Vector3& v);