public class Consumer extends Thread {
    private int thread_id;
    private Buffer buffer;

    public Consumer (int thread_id, Buffer b) {
        this.thread_id = thread_id;
        this.buffer = b;
    }

    public void run () {
        int value;

        while (true) {
            value = buffer.remove(this.thread_id);
        }
    }
}