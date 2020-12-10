a=[1]
def fun(x=a):
    print(x)
    print(id(x))
fun()
print(id(a));
a[0]=2
fun()
print(id(a));
a=[3]
fun()
print(id(a));
