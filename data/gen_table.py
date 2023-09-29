import math

def make_table(name, proc):
    tabl = []
    for i in range(0, 360):
        tabl.append(proc(math.radians(i)))
    tabl_str = ''
    for v in tabl:
        tabl_str += str(round(v, 6)) + 'f,\n'
    f = open(name, 'w')
    f.write(tabl_str)
    f.close()

if __name__ == '__main__':
    make_table('sin.txt', math.sin)
    make_table('cos.txt', math.cos)
    make_table('tan.txt', math.tan)
