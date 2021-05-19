import matplotlib.pyplot as plt
import numpy as np
def save_graph(x, y, filename):
    res = np.polyfit(x, y, 3)
    y_model = res[0]*0.73 * x ** 3
    plt.xlabel("N")
    plt.ylabel("time[s]")
    plt.yticks(np.arange(0, 4, 0.01))
    plt.plot(x, y_model, color="red")
    plt.plot(x, y)
    plt.savefig(filename)

def main():
    f = open("time.txt", "r")
    input_c = f.read().splitlines()
    f.close()

    time_c = []
    for s in input_c:
        time_c.append(float(s))

    x = np.array(range(len(time_c)))
    y = np.array(time_c)
    filename = "time_c_" + str(len(time_c)) + ".png"
    save_graph(x, y, filename)

if __name__ == "__main__":
    main()