public class Lab7 {
    public static void main (String[] args) {
        final int producers_qtty, consumers_qtty, buffer_size;
        Thread[] producers, consumers;
        Buffer buffer;
        
        /* verifica se foram passados argumentos o suficiente pela linha de comando */
        if ( args.length < 3 ) {
            System.out.println("Digite: java Lab7 <tamanho do buffer> " + 
                            " <número de produtoras> " + 
                            " <número de consumidoras>");
            System.exit(-1);
        }

        /* processa os argumentos de linha de comando */
        buffer_size = Integer.parseInt(args[0]);
        producers_qtty = Integer.parseInt(args[1]);
        consumers_qtty = Integer.parseInt(args[2]);

        /* inicializa o buffer */
        buffer = new Buffer(buffer_size);

        /* cria as threads consumidoras */
        consumers = new Consumer[consumers_qtty];
        for (int i = 0; i < consumers_qtty; i++) {
            consumers[i] = new Consumer(i, buffer);
        }

        /* cria as threads produtoras */
        producers = new Producer[producers_qtty];
        for (int i = 0; i < producers_qtty; i++) {
            producers[i] = new Producer(i + consumers_qtty, buffer);
        }

        /* inicia as threads consumidoras */
        for (int i = 0; i < consumers_qtty; i++) {
            consumers[i].start();
            System.out.println("consumidor " + i + " iniciado");
        }

        /* inicia as threads produtoras */
        for (int i = 0; i < producers_qtty; i++) {
            producers[i].start();
            System.out.println("produtor " + (consumers_qtty + i) + 
                            " iniciado");
        }

        System.out.println("-- Fim da thread principal");
    }
}