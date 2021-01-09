import copy
import numpy as np

def perceptron(x,y,max_iter=10e4):
    # Note: y should be -1 and 1 array!
    y=2*y-1
    b=np.ones((x.shape[0],1))
    X=np.concatenate((x,b),axis=1)
    print(x.shape)
    print()
    print(X.shape)
    w=np.random.rand(X.shape[1],1)
    i=0
    while np.sum(X.dot(w)!=y)!=0 and i<max_iter:
        for i in range(X.shape[0]):
            if X[i].dot(w)*y[i]<0:
                w=w-y[i]*np.vstack(X[i])
        i+=1
        print(np.sum(X.dot(w)!=y))
    return w
    
    
def pocket(x,y,max_iter=10e4):
    # Note: y should be -1 and 1 array!
    y=2*y-1
    b=np.ones((x.shape[0],1))
    X=np.concatenate((x,b),axis=1)
    w=np.random.rand(X.shape[1],1)
    loss=np.sum(X.dot(w_best)!=y)
    i=0
    w_best=copy(w)
    best_loss=loss
    while loss!=0 and i<max_iter:
        i+=1
        for i in range(X.shape[0]):
            if X[i].dot(w)*y[i]<0:
                w=w-y[i]*np.vstack(X[i])
        loss=np.sum(X.dot(w_best)!=y)
        if best_loss>loss:
            w_best=copy(w)
            best_loss=loss
    return w_best

def adaline(x,y,max_iter=10e4):
    b=np.ones((x.shape[0],1))
    X=np.concatenate((x,b),axis=1)
    w=np.random.rand(X.shape[1],1)
    i=0
    while i<max_iter:
         for i in range(X.shape[0]):
            e=2*(X[i].dot(w)-y[i])/m
            if e!=0:
                w=w-e*np.vstack(X[i])
    return w