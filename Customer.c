Customer()
{    
    web_reg_save_param_json(
        "ParamName=CustomerResponse",
        "QueryString=$",
        SEARCH_FILTERS,
        "Scope=Body",
        LAST);

    web_add_header("Authorization", "Bearer {authToken}");
    web_add_header("Accept", "application/json");

    lr_output_message("Auth Token = %s",
        lr_eval_string("{authToken}")
    );
    
    web_url("Customer_API",
        "URL=https://qa.api.edp.henryschein.com/api/customers/{customerId}",
        "Resource=0",
        "RecContentType=application/json",
        LAST);
    {
        int statusCode;
        statusCode = web_get_int_property(HTTP_INFO_RETURN_CODE);

        if (statusCode != 200)
        {
            lr_error_message("Response Code: %d", statusCode);
            return -1;
        }
        
            lr_output_message("Response Code: %d", statusCode);
    }

    lr_output_message("Customer API Response:\n%s",
        lr_eval_string("{CustomerResponse}")
    );

    return 0;
}
