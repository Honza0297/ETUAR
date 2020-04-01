 /************************************************      */
 /*  Educational tutorial for Arduino in robotics       */
 /*  Vyukovy Tutorial pro pouziti Arduina v robotice    */
 /*  File: vectors.h                                    */
 /*  Author: Pololu & Jan Beran                         */
 /*  Date: March 2020                                   */
 /*                                                     */
 /* This file is a part of author´s bachelor thesis     */
 /*                                                     */ 
 /* Funkce jsou prevzaty nebo jsou inspirovany funkcemi z */
 /* https://github.com/pololu/minimu-9-ahrs-arduino     */
 /*******************************************************/

#ifndef _DATATYPES_H
#define _DATATYPES_H 1

/**
 * Vzor pro vektor
 * */
template <typename T> struct vector
{
    T x, y, z;
};

/**
 * Vektorovy soucin
 * */
template <typename Ta, typename Tb, typename To> void vector_cross(const vector<Ta> *a, const vector<Tb> *b, vector<To> *out)
{
  out->x = (a->y * b->z) - (a->z * b->y);
  out->y = (a->z * b->x) - (a->x * b->z);
  out->z = (a->x * b->y) - (a->y * b->x);
}

/**
 * Skalarni soucin
 * */
template <typename Ta, typename Tb> float vector_dot(const vector<Ta> *a, const vector<Tb> *b)
{
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

template <typename T> void vector_normalize(vector<T> *a)
{
  float mag = sqrt(vector_dot(a, a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}
#endif