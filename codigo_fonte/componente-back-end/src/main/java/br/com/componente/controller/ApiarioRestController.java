package br.com.componente.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import br.com.componente.entidades.DadosApiario;
import br.com.componente.entidades.DadosApiarioRequisicao;
import br.com.componente.servicos.ApiarioImpl;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiResponses;
import io.swagger.annotations.ApiResponse;


@RestController(value="API para salvar as informações da colmeia")
@Api(description="API para salvar as informações da colmeia")
public class ApiarioRestController {
	
	@Autowired
	 private ApiarioImpl apiarioImpl;

	 
	 @ApiOperation(value = "Salvar dados da colmeia")
	 @ApiResponses(value = {
			    @ApiResponse(code = 200, message = "Sucesso ao salvar os dados")
			})
	 @RequestMapping(value = "/salvar", method = RequestMethod.POST,  produces="text/plain")	 
	 public void salvarDadosApiario(@RequestBody DadosApiarioRequisicao dadosApiarioRequisicao) throws Exception{		
		
		 DadosApiario dadosApiario = new DadosApiario();
		 dadosApiario.setContadorAnaliseAtividadeEnxame(dadosApiarioRequisicao.getContadorAnaliseAtividadeEnxame());
		 dadosApiario.setGas(dadosApiarioRequisicao.getGas());
		 dadosApiario.setPeso(dadosApiarioRequisicao.getPeso());
		 dadosApiario.setSom(dadosApiarioRequisicao.getSom());
		 dadosApiario.setTemperatura(dadosApiarioRequisicao.getTemperatura());
		 dadosApiario.setTenantId(dadosApiarioRequisicao.getTenantId());
		 dadosApiario.setUmidade(dadosApiarioRequisicao.getUmidade());
		 
		 apiarioImpl.salvarDadosApiario(dadosApiario); 

	  }
	    
	
	
}
