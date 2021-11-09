package br.com.componente.servicos;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import br.com.componente.entidades.DadosApiario;
import br.com.componente.repositorio.ApiarioRepository;

@Service
public class ApiarioImpl {

	@Autowired
	private ApiarioRepository apiarioRepository;
	
	public void salvarDadosApiario(DadosApiario dadosApiario){
		
		apiarioRepository.save(dadosApiario);
		
	}
}
