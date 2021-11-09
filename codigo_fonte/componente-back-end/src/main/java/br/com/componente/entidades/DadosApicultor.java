package br.com.componente.entidades;

public class DadosApicultor {

	private Long idTenant;
	private String nome;
	private String senha;
	private String endereco;
	public Long getIdTenant() {
		return idTenant;
	}
	public void setIdTenant(Long idTenant) {
		this.idTenant = idTenant;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getSenha() {
		return senha;
	}
	public void setSenha(String senha) {
		this.senha = senha;
	}
	public String getEndereco() {
		return endereco;
	}
	public void setEndereco(String endereco) {
		this.endereco = endereco;
	}
	
}
