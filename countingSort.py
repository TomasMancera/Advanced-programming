from random import randint
import time

from random import randint
import time

def generate_random(lowlimit, suplimit):
    return randint(lowlimit, suplimit)


def write_data(filename):
    file = open(filename, "a") 
    for _ in range(1048576):
        file.write(f'{generate_random(0, 16383)} \n')
    file.close()

def read_data(filename):
    num_list = []
    with open(filename, encoding = 'utf-8') as f:
        for i in f:
            num_list.append(int(i))
    return num_list, max(num_list)

def write_sorted_data(filename, list):
    file = open(filename, "a") 
    for i in list:
        file.write(f'{i} \n')
    file.close()

def count_sort(odd_list, maxi):
    list_count = [0] * (maxi + 1)
    list_sorted = [None] * len(odd_list)
    
    for i in odd_list:
        list_count[i] += 1
        
    total = 0
    for i in range(len(list_count)):
        list_count[i], total = total, total + list_count[i]
    
    for index in odd_list:
        list_sorted[list_count[index]] = index
        list_count[index] +=1
    return list_sorted



def main():
    #write_data("numbers.txt")
    start = time.time() 
    num_list, maxi = read_data("numbers.txt")
    sorted_list = count_sort(num_list, maxi)
    write_sorted_data("sortednumbers.txt", sorted_list)
    end = time.time()

    print(f"RunTime was: {end-start}")

main()