def p():
    a=10
    print(a**2)
    return [[a,a**2*2],[a*3,a**2*2],[a*4,a**2*2],[a*4,a**2*4]]

def pp(l):
    print("here")
    for t in l:
        print(t,end=" ")
    print(" ")

print("Lib loaded sucessfully!")