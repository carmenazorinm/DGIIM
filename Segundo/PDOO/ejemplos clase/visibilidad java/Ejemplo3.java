interface Doblable{
	void doblar();
}

class Enrollador <T extends Doblable>{
	public void enrollar(T t){
		t.doblar();
		System.out.println("Enrollado\n");
	}
}

class Mapa implements Doblable{
	@Override
	public void doblar(){
		System.out.println("Doblando Mapa\n");
	};
}
	
class Alfombra implements Doblable{
	@Override
	public void doblar(){
		System.out.println("Doblando Alfombra\n");
	};
}

class Kebab implements Doblable{
	@Override
	public void doblar(){
		System.out.println("Doblando Kebab\n");
	};
}

