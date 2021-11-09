package br.com.componente.servicos;


import java.util.List;

import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.RequestBody;
import br.com.componente.entidades.DadosApiario;
import br.com.componente.entidades.DadosApicultor;
import br.com.componente.entidades.DadosColetados;
import br.com.componente.entidades.DadosColmeia;
import br.com.componente.entidades.FiltroBuscaDadosApiario;
import br.com.componente.entidades.FiltroBuscaDadosApicultor;
import br.com.componente.entidades.FiltroBuscaDadosColetados;
import br.com.componente.entidades.FiltroBuscaDadosColmeia;

@Service
public class ApiculturaImpl {
		 
	 public void salvarDadosColetados(DadosColetados dadosColetados) {

	  }
	 
	
	 	 
	 public void salvarDadosApicultor(@RequestBody DadosApicultor dadosApicultor){		
 

	  }
	 
		 
	 public void salvarDadosColmeia(@RequestBody DadosColmeia dadosColmeia) {		
				
		 
		// apiarioImpl.salvarDadosApiario(dadosApiario); 

	  }
	 
	 
	 public void salvarDadosApiario(@RequestBody DadosApiario dadosApiario) {	
		// apiarioImpl.salvarDadosApiario(dadosApiario); 

	  }
	 
	
	 public List<DadosColetados> buscaDadosColetados(@RequestBody FiltroBuscaDadosColetados filtro) {	
		 return null;
	  }
	 
	  
	 public List<DadosApicultor> buscaDadosApicultor(@RequestBody FiltroBuscaDadosApicultor filtro) {	
		 return null;
	  }
	 
	
	 public List<DadosApicultor> buscaDadosApiario(@RequestBody FiltroBuscaDadosApiario filtro) {	
		 return null;
	 }
	 
	 
	 public List<DadosApicultor> buscaDadosColmeia(@RequestBody FiltroBuscaDadosColmeia filtro) {	
		 return null;
	 }
	 
	
}
