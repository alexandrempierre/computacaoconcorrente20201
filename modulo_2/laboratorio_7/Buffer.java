import java.util.List;
import java.util.ArrayList;

public class Buffer {
    private int[] stored_values;
    private boolean[] empty_position;

    private final int size;
    private int in, out;

    public Buffer (final int size) {
        this.in = 0;
        this.out = 0;
        this.size = size;
        
        this.stored_values = new int[size];
        this.empty_position = new boolean[size];
        
        /* inicializa o buffer vazio */
        for (int i = 0; i < this.size; i++) {
            this.stored_values[i] = -1;
            this.empty_position[i] = true;
        }
    }

    private int getSize () {
        return this.size;
    }

    private int countEmptyPositions () {
        int empty_count = 0;

        for (boolean empty : this.empty_position) {
            if ( empty ) { empty_count++; }
        }

        return empty_count;
    }

    private boolean isFull () {
        return this.countEmptyPositions() == 0;
    }

    private boolean isEmpty () {
        return this.countEmptyPositions() == this.size;
    }

    public synchronized void insert (int thread_id) {
        int value = thread_id;

        try {
            while ( this.isFull() ) {
                System.out.println("produtor " + thread_id + 
                                " bloqueado: buffer cheio");
                wait();
                System.out.println("produtor " + thread_id + " desbloqueado");
            }
            
            this.print("Buffer antes: ");
            System.out.println("produtor " + thread_id + " inserindo valor " + 
                            value + " na posição " + in + " do buffer");

            this.stored_values[in] = value;
            this.empty_position[in] = false;
            this.print("Buffer depois: ");

            in = (in + 1) % this.size;

            notifyAll(); // Não pode ser notify() porque isso poderia gerar deadlock

        } catch (InterruptedException e) { }
    }

    public synchronized int remove (int thread_id) {
        int ret = -1;

        try {
            while ( this.isEmpty() ) {
                System.out.println("consumidor " + thread_id + 
                                " bloqueado: buffer vazio");
                wait();
                System.out.println("consumidor " + thread_id + 
                                " desbloqueado");
            }
            
            System.out.println("consumidor " + thread_id + 
                            " procurando posição preenchida no buffer");
            
            ret = new Integer(this.stored_values[out]);

            this.print("Buffer antes: ");
            System.out.println("consumidor " + thread_id + 
                            " removendo valor " + ret + " da posição " + out + 
                            " do buffer");
            
            this.empty_position[out] = true;
            this.print("Buffer depois: ");

            out = (out + 1) % this.size;
            notifyAll(); // Não pode ser notify() porque isso poderia gerar deadlock

            return ret;

        } catch (InterruptedException e) { return ret; }
    }

    public String toString () {
        String str = "";

        for (int i = 0; i < this.size; i++) {
            if ( this.empty_position[i] ) {
                str += "vazio";
            }
            else {
                str += this.stored_values[i];
            }

            str += i == this.size - 1 ? "" : ", ";
        }
        
        return "{ " + str + " }";
    }

    public void print (String pre) {
        System.out.println(pre + this.toString());
    }    
}