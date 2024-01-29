
class TablaHash{
    private:
        int indice;
        int* valor;
    public:
        TablaHash ();
        void insertar(int valor);
        void eliminar(int& valor);
        void buscar(int& valor);
        void imprimir(TablaHash& datos);

};
