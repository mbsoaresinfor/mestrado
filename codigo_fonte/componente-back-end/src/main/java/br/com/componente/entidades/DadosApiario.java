package br.com.componente.entidades;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "dados")
public class DadosApiario implements Serializable{

	
	private static final long serialVersionUID = -4021164211840850744L;

	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	private long id;

	
	@Column(name = "tenantId")
	private Float tenantId;
	
	@Column(name = "contadorAnaliseAtividadeEnxame")
	private Float contadorAnaliseAtividadeEnxame;
	
	@Column(name = "gas")
	private Float gas;
	
	@Column(name = "temperatura")
	private Float temperatura;
	
	@Column(name = "umidade")
	private Float umidade;
	
	@Column(name = "som")
	private Float som;
	
	@Column(name = "peso")
	private Float peso;

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public Float getTenantId() {
		return tenantId;
	}

	public void setTenantId(Float tenantId) {
		this.tenantId = tenantId;
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
