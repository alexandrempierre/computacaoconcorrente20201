public class SumTask implements Runnable {
    private int tid, nthreads;
    private Vector A, B, C;

    public SumTask (int tid, int nthreads, Vector A, Vector B, Vector C) {
        this.tid = tid;
        this.nthreads = nthreads;
        this.A = A;
        this.B = B;
        this.C = C;
    }

    public void run () {
        int s;
        for (int i = tid; i < this.C.getLength(); i += this.nthreads) {
            s = this.A.getElementAt(i) + this.B.getElementAt(i);
            this.C.setElementAt(i, s);
        }

        System.out.println("-- Fim da soma na thread " + this.tid);
    }
}