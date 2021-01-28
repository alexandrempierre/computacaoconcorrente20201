public class Producer extends Thread {
    private int thread_id;
    private Buffer buffer;

    public Producer (int thread_id, Buffer b) {
        this.thread_id = thread_id;
        this.buffer = b;
    }

    public void run () {
        while (true) {
            buffer.insert(this.thread_id);
        }
    }
}