void display7SEG(int counter,
		GPIO_TypeDef* port0, uint16_t pin0,
		GPIO_TypeDef* port1, uint16_t pin1,
		GPIO_TypeDef* port2, uint16_t pin2,
		GPIO_TypeDef* port3, uint16_t pin3,
		GPIO_TypeDef* port4, uint16_t pin4,
		GPIO_TypeDef* port5, uint16_t pin5,
		GPIO_TypeDef* port6, uint16_t pin6){
	switch(counter){
	case 0:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, RESET);
		HAL_GPIO_WritePin(port5, pin5, RESET);
		HAL_GPIO_WritePin(port6, pin6, SET);
		break;
	case 1:
		HAL_GPIO_WritePin(port0, pin0, SET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, SET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, SET);
		HAL_GPIO_WritePin(port6, pin6, SET);
		break;
	case 2:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, SET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, RESET);
		HAL_GPIO_WritePin(port5, pin5, SET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, SET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(port0, pin0, SET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, SET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, RESET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, SET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, RESET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, SET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, RESET);
		HAL_GPIO_WritePin(port5, pin5, RESET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, SET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, SET);
		HAL_GPIO_WritePin(port6, pin6, SET);
		break;
	case 8:
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, RESET);
		HAL_GPIO_WritePin(port5, pin5, RESET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(port0, pin0, RESET);
		HAL_GPIO_WritePin(port1, pin1, RESET);
		HAL_GPIO_WritePin(port2, pin2, RESET);
		HAL_GPIO_WritePin(port3, pin3, RESET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, RESET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
		break;
	default:
		HAL_GPIO_WritePin(port0, pin0, SET);
		HAL_GPIO_WritePin(port1, pin1, SET);
		HAL_GPIO_WritePin(port2, pin2, SET);
		HAL_GPIO_WritePin(port3, pin3, SET);
		HAL_GPIO_WritePin(port4, pin4, SET);
		HAL_GPIO_WritePin(port5, pin5, SET);
		HAL_GPIO_WritePin(port6, pin6, RESET);
	}
}
