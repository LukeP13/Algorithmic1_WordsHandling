#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <string>

class myexception: public std::exception {
    private:
      std::string _message;
    public:
        /**	@brief Constructor amb parametres
            @pre Cert
            @post Excepció creada amb missatge el missatge 'message' */
        myexception(const std::string message);

        /**	@brief Elimina l'excepcio
            @pre Cert
            @post Elimina l'excepcio */
        virtual ~myexception() throw();

        /**	@brief Retorna el missatge de l'excepcio
            @pre Cert
            @post _message retornat */
        virtual const char* what() const throw();
          // Nota: trow() indica que aquest mètode no llançarà cap excepció
          //       (es cridarà std::unexpected si es produeix una excepció)
};

#endif
