package br.com.componente.controller;


import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import br.com.componente.entidades.DadosApiario;
import br.com.componente.entidades.DadosApicultor;
import br.com.componente.entidades.DadosColetados;
import br.com.componente.entidades.DadosColmeia;
import br.com.componente.entidades.FiltroBuscaDadosApiario;
import br.com.componente.entidades.FiltroBuscaDadosApicultor;
import br.com.componente.entidades.DadosColetados;
import br.com.componente.entidades.FiltroBuscaDadosColetados;
import br.com.componente.entidades.FiltroBuscaDadosColmeia;
import br.com.componente.servicos.ApiculturaImpl;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiResponses;
import io.swagger.annotations.ApiResponse;


@RestController(value="API para manipulação das informações do componente back-end")
@Api(description="API para manipulação das informações do componente back-end")
public class ApiculturaRestController {
	
	@Autowired
	 private ApiculturaImpl apiculturaImpl;

	 
	 @ApiOperation(value = "Salvar os dados coletados da colmeia")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao salvar os dados")
			})
	 @RequestMapping(value = "/salvarDadosColetados", method = RequestMethod.POST,  produces="text/plain")	 
	 public void salvarDadosColetados(@RequestBody DadosColetados dadosColetados) throws Exception{
		 
		 apiculturaImpl.salvarDadosColetados(dadosColetados); 

	  }
	 
	 @ApiOperation(value = "Salvar os dados do apicultor")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao salvar os dados")
			})
	 @RequestMapping(value = "/salvarDadosApicultor", method = RequestMethod.POST,  produces="text/plain")	 
	 public void salvarDadosApicultor(@RequestBody DadosApicultor dadosApicultor){		
				
		 
		 apiculturaImpl.salvarDadosApicultor(dadosApicultor); 

	  }
	 
	 @ApiOperation(value = "Salvar os dados da colmeia")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao salvar os dados")
			})
	 @RequestMapping(value = "/salvarDadosColmeia", method = RequestMethod.POST,  produces="text/plain")	 
	 public void salvarDadosColmeia(@RequestBody DadosColmeia dadosColmeia) {	
		 
		 apiculturaImpl.salvarDadosColmeia(dadosColmeia); 

	  }
	 
	 @ApiOperation(value = "Salvar os dados do apiario")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao salvar os dados")
			})
	 @RequestMapping(value = "/salvarDadosApiario", method = RequestMethod.POST,  produces="text/plain")	 
	 public void salvarDadosApiario(@RequestBody DadosApiario dadosApiario) throws Exception{
		 apiculturaImpl.salvarDadosApiario(dadosApiario); 
	  }
	 
	 
	 @ApiOperation(value = "Busca os dados coletados da colmeia")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao buscar os dados")
			})
	 @RequestMapping(value = "/buscaDadosColetados", method = RequestMethod.GET)	 
	 public List<DadosColetados> buscaDadosColetados(@RequestBody FiltroBuscaDadosColetados filtro) {	
		 return apiculturaImpl.buscaDadosColetados(filtro);
	  }
	 
	 @ApiOperation(value = "Busca os dados do Apicultor")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao buscar os dados")
			})
	 @RequestMapping(value = "/buscaDadosApicultor", method = RequestMethod.GET)	 
	 public List<DadosApicultor> buscaDadosApicultor(@RequestBody FiltroBuscaDadosApicultor filtro) {	
		 return apiculturaImpl.buscaDadosApicultor(filtro);
	  }
	 
	 @ApiOperation(value = "Busca os dados do Apiario")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao buscar os dados")
			})
	 @RequestMapping(value = "/buscaDadosApiario", method = RequestMethod.GET)	 
	 public List<DadosApicultor> buscaDadosApiario(@RequestBody FiltroBuscaDadosApiario filtro) {	
		 return apiculturaImpl.buscaDadosApiario(filtro);
	 }
	 
	 @ApiOperation(value = "Busca os dados da Colmeia")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao buscar os dados")
			})
	 @RequestMapping(value = "/buscaDadosColmeia", method = RequestMethod.GET)	 
	 public List<DadosApicultor> buscaDadosColmeia(@RequestBody FiltroBuscaDadosColmeia filtro) {	
		 return apiculturaImpl.buscaDadosColmeia(filtro);
	 }
	    
	
	
}
