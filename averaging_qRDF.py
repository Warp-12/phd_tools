import numpy as np


def readFiles(fileName):
    values = []
    with open(fileName, "r") as inFile:
        lines = inFile.readlines()
        for line in lines[:]:
            values.append(line)
    return values


if __name__ == '__main__':
    index = 8514
    temp = 500
    file1Values = readFiles('bot_AlSi_' + str(temp) +
                            '_' + str(index) + '.txt')
    file2Values = readFiles('bot_AlSi_' + str(temp) +
                            '_' + str(index+1) + '.txt')
    file3Values = readFiles('bot_AlSi_' + str(temp) +
                            '_' + str(index+2) + '.txt')

    column0 = [[0 for i in range(len(file1Values))] for j in range(4)]
    column1 = [[0 for i in range(len(file1Values))] for j in range(4)]
    column2 = [[0 for i in range(len(file1Values))] for j in range(4)]
    column3 = [[0 for i in range(len(file1Values))] for j in range(4)]

    i = 0
    for line in file1Values:
        separatedLine = line.split()
        column0[0][i] = float(separatedLine[0])
        column1[0][i] = float(separatedLine[1])
        column2[0][i] = float(separatedLine[2])
        column3[0][i] = float(separatedLine[3])
        i += 1

    i = 0
    for line in file2Values:
        separatedLine = line.split()
        column0[1][i] = float(separatedLine[0])
        column1[1][i] = float(separatedLine[1])
        column2[1][i] = float(separatedLine[2])
        column3[1][i] = float(separatedLine[3])
        i += 1

    i = 0
    for line in file3Values:
        separatedLine = line.split()
        column0[2][i] = float(separatedLine[0])
        column1[2][i] = float(separatedLine[1])
        column2[2][i] = float(separatedLine[2])
        column3[2][i] = float(separatedLine[3])
        i += 1

    j = i
    i = 0
    for index in range(j):
        column0[3][i] = (column0[0][i] + column0[1][i] + column0[2][i]) / 3.0
        column1[3][i] = (column1[0][i] + column1[1][i] + column1[2][i]) / 3.0
        column2[3][i] = (column2[0][i] + column2[1][i] + column2[2][i]) / 3.0
        column3[3][i] = (column3[0][i] + column3[1][i] + column3[2][i]) / 3.0
        i += 1

with open('ave_qRDF_Al_' + str(temp) + '.txt', 'w') as f:
    for index in range(i):
        f.write(str(column0[3][index]) + " " + str(column1[3][index]) +
                " " + str(column2[3][index]) + " " + str(column3[3][index]) + "\n")
