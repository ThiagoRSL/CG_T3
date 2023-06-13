

Extras:
- Disparo de rajadas com efeitos visuais bonitos: Particulas adicionadas no deslocamento da nave e dos disparos.
- Simulação da explosão dos inimigos: altera a cor dos elementos para laranja/amarelo (simulando sobreaquecimento).
- Inimigos que se movem na tela com alguma IA: quando o jogador sai do campo de visão do inimigo ele se desloca até próximo ao último ponto
conhecido do jogador.

FAZER
- Munições especiais que buscam o inimigo calculando trajetórias curvas:
- Power-ups para disparos especiais, ou escudo: poderes que podem ser utilizados com o consumo de energia (barrinha azul), ao pressionar as teclas 1, 2 e 3.


Outros Possíveis Extras:
- Mecanismo de Otimização de Renderização: renderiza apenas elementos próximos (aplicável à curvas e personagens), visivel atraves da alteração da constante 
RENDER_DISTANCE no RenderManager.h (é visível a diferença do desempenho nas curvas pela presença de tantos pontos);