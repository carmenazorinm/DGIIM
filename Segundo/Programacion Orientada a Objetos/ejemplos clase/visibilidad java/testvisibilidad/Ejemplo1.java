//package testvisibilidad;

class otraClase{
	int atributo=111;
}

class TestVisibilidad{
	public static void main(String[] args){
		otraClase o=new otraClase();
		System.out.println(o.atributo);
		o.atributo=333;
		System.out.println(o.atributo);
	}
}
