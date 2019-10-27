#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Net/MediaType.h"
#include "Adapter/Validator/HttpMethods.h"
#include "Adapter/Http/ErrorJsonAPIParser.h"
#include "Foundation/Http/AbstractResource.h"
#include "Foundation/Http/CORSHeadersFactory.h"
#include "Adapter/Validator/HttpContentTypeHeaders.h"

namespace Foundation {
namespace Http {


    void AbstractResource::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        response.setContentType(Poco::Net::MediaType("application/vnd.api+json"));
        try {

            auto httpMethod = ::Validator::HttpMethods(request);
            if ( !httpMethod.valid() )
                throw Poco::Exception("Method Not Allowed", httpMethod.message(), 405);

            auto mediaType = ::Validator::HttpContentTypeHeaders(request);
            if ( !mediaType.valid() )
                throw Poco::Exception("Unsupported Media Type", mediaType.message(), 415);

            corsHeaders(response);

            if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET )
                this->handle_get(request, response);

            if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT )
                this->handle_put(request, response);

            if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST )
                this->handle_post(request, response);

            if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_PATCH )
                this->handle_patch(request, response);

            if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE )
                this->handle_delete(request, response);

            if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS )
                this->handle_options(request, response);

        } catch (Poco::Exception & exception) {

            std::string responseError;
            Poco::URI uri = Poco::URI(request.getURI());
            response.setStatusAndReason((Poco::Net::HTTPResponse::HTTPStatus) exception.code());

            responseError = errorParser()->toJson(
                request.getHost(),
                std::to_string(exception.code()),
                uri.getPath(),
                response.getReason(),
                exception.message().substr(exception.message().find(':')+1)
            );

            response.sendBuffer(responseError.data(), responseError.length());

        }

        if ( response.getContentLength() == -1 )
            response.setContentLength(Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH);

        if ( !response.sent() )
            response.send().flush();
    }

    void AbstractResource::corsHeaders(Poco::Net::HTTPServerResponse & response)
    {
        std::map<std::string, std::string> headersSet = corsHeaders();
        for ( auto & header : headersSet )
            response.set(header.first, header.second);
    }

    std::map<std::string, std::string> AbstractResource::corsHeaders()
    {
        return CORSHeadersFactory::create()->headers();
    }

    std::unique_ptr<ErrorParserInterface> AbstractResource::errorParser()
    {
        return std::make_unique<::Http::ErrorJsonAPIParser>();
    }

    void AbstractResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
	    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_patch(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_delete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    void AbstractResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }


} }