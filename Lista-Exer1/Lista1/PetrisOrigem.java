 package ListaDeExercicio1;

import java.util.Scanner;


class No{
    
    int pedra;
    No proximo;

    No(int pedra){
        this.pedra=pedra;
        this.proximo=null;
    }
}

public class PetrisOrigem {
     No head=null; 

 //_______________________________________  INCLUIR NO _____________________________________________________________//

    public void inserirNo(PetrisOrigem pilha, int pedra){
         No no=new No(pedra);
        int chamarRemover=0;
        if(this.head==null){ //caso a cabeca nao aponte para nenhum no, ela recebe o primeiro no criado
            this.head=no;

        }else{
             //remover os 2 dois nos de cima caso sejam iguais 
            if(head.pedra==pedra){
                chamarRemover=1;
            }

            no.proximo=head;
            head=no;

           
        }
        if(chamarRemover==1){
             removerNo(pilha);
            removerNo(pilha);
            chamarRemover=0;
        }
       
     
    }

//_______________________________________  REMOVER NO _____________________________________________________________//


   
    public void removerNo(PetrisOrigem pilha){
    
        No atual= pilha.head;

        if(pilha.head==null){ //caso a cabeca nao aponte para nenhum no, retorna mensagem de lista vazia
            System.out.println("A lista esta vazia.");

        }else{ 
          
            pilha.head=atual.proximo;
         
          
        }
        
    }


//_______________________________________  PRINTAR LISTA _____________________________________________________________//

    public void printar(PetrisOrigem pilha){
         
            No aux =pilha.head;
            while(aux!=null){
                System.out.println(aux.pedra);
                aux=aux.proximo;
                
            }
           
        
    }
//_______________________________________  RETORNA QUANT DE PEDRAS _____________________________________________________________//

    public int QuantDePedrasRestantes(){
           int contador=0;
         No aux =this.head;
            
            if(aux!=null){

                while(aux!=null){
                    contador++;
                    aux=aux.proximo;
               }
            
            }else{
                contador=0;
            }
           return contador;
        
    }  

//_______________________________________  RETORNA PEDRA DO TOPO _____________________________________________________________//

    public int pedraDoTopo(){
            No aux =this.head;
            No pedraSobra=this.head;
           int pedraDoTopo;

            if(aux!=null){
                pedraDoTopo=pedraSobra.pedra;  
            }else{
              pedraDoTopo=-1; 
            }  

           return pedraDoTopo;


        }
// _______________________________________________ MAIN ________________________________________________________________//
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String pedraS;
        int pedra=0,p;

        PetrisOrigem jogo = new PetrisOrigem();

        p = scan.nextInt();
        int restoDePedras[]=new int[p];
        int pedraDoTopo[]=new int[p];

        for (int cont = 0; cont < p; cont++) {
            jogo=new PetrisOrigem();
         while (true) {
                 pedraS = scan.next();
           
            if (pedraS.equals("END")) {
                pedraDoTopo[cont]=jogo.pedraDoTopo();
                restoDePedras[cont]=jogo.QuantDePedrasRestantes();
                break;

            }else{
                pedra=Integer.parseInt(pedraS);
                jogo.inserirNo(jogo, pedra);   
            }

         }
    
        } 

         for (int cont = 0; cont < p; cont++) {
            System.out.println("Caso "+ cont + ": "+restoDePedras[cont] +" "+pedraDoTopo[cont]);
         }
}

}