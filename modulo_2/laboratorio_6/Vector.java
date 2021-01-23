public class Vector {
    private int[] array;
    private int length;

    /* Construtores */
    public Vector (int len) {
        this.length = len;
        this.init();
    }

    public Vector (int len, int val) {
        this.length = len;
        this.init(val);
    }

    public Vector (int len, int[] vals) {
        this.length = len;
        this.init(vals);
    }

    /* Inicializadores */
    public void init () {
        this.array = new int[this.getLength()];
    }

    public void init (int val) {
        this.init();

        for (int i = 0; i < this.getLength(); i++) {
            array[i] = val;
        }
    }

    public void init (int[] vals) {
        this.init();

        for (int i = 0; i < this.getLength(); i++) {
            array[i] = vals[i % vals.length];
        }
    }

    /* Outros métodos */
    public int getLength () {
        return this.length;
    }

    public int getElementAt (int index) {
        return this.array[index];
    }

    public void setElementAt (int index, int val) {
        this.array[index] = val;
    }

    /* Método para facilitar a impressão dos resultados */
    public String toString () {
        String buffer = "{";
        for (int i = 0; i < this.getLength(); i++) {
            if (i >= 1) {
                buffer += ", ";
            }
            buffer += this.array[i];
        }
        buffer += "}";
        
        return buffer;
    }
}