public class Lab6 {
    private static final int nthreads = 4, len = 20;

    public static void main (String[] args) {
        Thread[] threads = new Thread[nthreads];

        Vector A, B, C;
        A = new Vector(len, 65);
        B = new Vector(len, new int[]{0, -20, 440});
        C = new Vector(len);

        /* Cria das threads */
        for (int i = 0; i < threads.length; i++) {
            System.out.println("-- Cria a thread " + i);
            threads[i] = new Thread( new SumTask(i, nthreads, A, B, C) );
        }

        /* Inicia as threads */
        for (int i = 0; i < threads.length; i++) {
            threads[i].start();
        }

        /* Aguarda o fim das threads */
        for (int i = 0; i < threads.length; i++) {
            try {
                threads[i].join();
            } 
            catch (InterruptedException e) { 
                return ;
            }

            System.out.println("-- Join da thread " + i);
        }

        System.out.println("Vetor C");
        System.out.println(C);
    }
}