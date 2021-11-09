package br.com.componente.repositorio;


import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import br.com.componente.entidades.DadosApiario;


@Repository
public interface ApiarioRepository  extends CrudRepository<DadosApiario, Long> {

	
}
