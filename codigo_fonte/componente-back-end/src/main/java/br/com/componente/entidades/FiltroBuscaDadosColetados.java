package br.com.componente.entidades;

import java.util.Date;

public class FiltroBuscaDadosColetados {

	private Long idTanant;
	private Long idColmeia;
	private Date data;
	
	public Long getIdTanant() {
		return idTanant;
	}
	public void setIdTanant(Long idTanant) {
		this.idTanant = idTanant;
	}
	public Long getIdColmeia() {
		return idColmeia;
	}
	public void setIdColmeia(Long idColmeia) {
		this.idColmeia = idColmeia;
	}
	public Date getData() {
		return data;
	}
	public void setData(Date data) {
		this.data = data;
	}
	
	
}
