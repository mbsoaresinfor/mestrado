package br.com.componente.entidades;


public class DadosColetados {


	private Float idTenant;
	
	private Float idColmeia;
	
	private Float contadorAnaliseAtividadeEnxame;
	
	private Float gas;
	
	private Float temperatura;

	private Float umidade;
	
	private Float som;
	
	private Float peso;	
		

	public Float getIdColmeia() {
		return idColmeia;
	}

	public void setIdColmeia(Float idColmeia) {
		this.idColmeia = idColmeia;
	}

	public Float getIdTenant() {
		return idTenant;
	}

	public void setIdTenant(Float idTenant) {
		this.idTenant = idTenant;
	}

	public Float getContadorAnaliseAtividadeEnxame() {
		return contadorAnaliseAtividadeEnxame;
	}

	public void setContadorAnaliseAtividadeEnxame(Float contadorAnaliseAtividadeEnxame) {
		this.contadorAnaliseAtividadeEnxame = contadorAnaliseAtividadeEnxame;
	}

	public Float getGas() {
		return gas;
	}

	public void setGas(Float gas) {
		this.gas = gas;
	}

	public Float getTemperatura() {
		return temperatura;
	}

	public void setTemperatura(Float temperatura) {
		this.temperatura = temperatura;
	}

	public Float getUmidade() {
		return umidade;
	}

	public void setUmidade(Float umidade) {
		this.umidade = umidade;
	}

	public Float getSom() {
		return som;
	}

	public void setSom(Float som) {
		this.som = som;
	}

	public Float getPeso() {
		return peso;
	}

	public void setPeso(Float peso) {
		this.peso = peso;
	}
	
}
