


class MNIST:
    def __init__(self):
        self.n = 60000
        self.qn = 1000
        self.d = 50
        self.name = 'Mnist'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )

class MNIST784:
    def __init__(self):
        self.n = 60000
        self.qn = 1000
        self.d = 784
        self.name = 'Mnist784'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )
        
class Trevi:
    def __init__(self):
        self.n = 100800
        self.qn = 1000
        self.d = 4096
        self.name = 'Trevi'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )
        
class Netflix:
    def __init__(self):
        self.n = 17500
        self.qn = 270
        self.d = 300
        self.name = 'Netflix'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )
        
class Sift:
    def __init__(self):
        self.n = 1000000
        self.qn = 1000
        self.d = 128
        self.name = 'Sift'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )
        
class Yahoo:
    def __init__(self):
        # self.n = 624961
        self.n = 620000
        # self.qn = 4961
        self.qn = 1000
        self.d = 300
        self.name = 'Yahoo'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )
        
class Gist:
    def __init__(self):
        self.n = 1000000
        self.qn = 1000
        self.d = 960
        self.name = 'Gist'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )

class Tiny:
    def __init__(self):
        self.n = 79302017 - 100
        self.qn = 100
        self.d = 384
        self.name = 'Tiny'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )

class MovieLens:
    def __init__(self):
        # self.n = 50000
        self.n = 52889
        # self.qn = 3889
        self.qn = 1000
        self.d  = 150
        self.name = 'MovieLens'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )

class Synthetic:
    def __init__(self):
        self.n = 1000000
        self.qn = 1000
        self.d  = 256
        self.name = 'synthetic'
        self.ds = '../data/%s/%s.ds'%(self.name, self.name)
        self.qs = '../data/%s/%s.q'%(self.name, self.name)
        self.of = 'results/%s/'%(self.name, )