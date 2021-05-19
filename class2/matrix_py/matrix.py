import numpy, sys, time
import matplotlib.pyplot as plt

def init(n):
    a = numpy.zeros((n, n)) # Matrix A
    b = numpy.zeros((n, n)) # Matrix B
    c = numpy.zeros((n, n)) # Matrix C

    # Initialize the matrices to some values.
    for i in range(n):
        for j in range(n):
            a[i, j] = i * n + j
            b[i, j] = j * n + i
            c[i, j] = 0
    return a, b, c

def calc_matrix_production(n, a, b, c): 
    for i in range(n):
        for j in range(n):
            for k in range(n):
                c[i, j] += a[i, k] * b[k, j]

def save_graph(x, y, filename):
    plt.plot(x, y)
    res3= numpy.polyfit(x, y, 3)
    y3 = res3[0] * x ** 3
    plt.xlabel("N")
    plt.ylabel("time[s]")
    plt.plot(x, y3, color="red")
    plt.savefig(filename)

def ans_checker(c, n):
    # Print C for debugging. Comment out the print before measuring the execution time.
    total = 0
    for i in range(n):
        for j in range(n):
            print(c[i, j])
            total += c[i, j]
    # Print out the sum of all values in C.
    # This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
    print("sum: %.6f" % total)

def main():
    if (len(sys.argv) != 2):
        print("usage: python %s N" % sys.argv[0])
        quit()
    
    n = int(sys.argv[1])
    time_list = []
    n_list = []
    for i in range(n):
        a, b, c = init(i)
        begin = time.time()
        calc_matrix_production(i, a, b, c)
        end = time.time()
        time_list.append(end - begin)
        n_list.append(i)
    
    x = numpy.array(n_list)
    y = numpy.array(time_list)
    filename = "time_py_"+ str(n) + ".png"
    save_graph(x, y, filename)

if __name__ == "__main__":
    main()