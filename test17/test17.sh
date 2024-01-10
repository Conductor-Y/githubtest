#!/bin/bash
set -e

echo "Creat database"
./ex17 db.dat c 100 100 Conductor
echo ""

echo "set database Yjh, Tzq, Mo"
./ex17 db.dat s 1 Yjh Yjh@.com male
./ex17 db.dat s 2 Tzq Tzq@.com female
./ex17 db.dat s 3 Mo Mo@.com none
echo ""

echo "list all"
./ex17 db.dat l
echo ""

echo "Delete the record by id 3"
./ex17 db.dat d 3
echo ""

echo "Find name Mo record"
./ex17 db.dat f Mo
echo ""

echo "list all"
./ex17 db.dat l
echo ""

echo "Get record by id 1"
./ex17 db.dat g 1
echo ""
