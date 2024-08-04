
const nodemailer = require('nodemailer');


let transporter = nodemailer.createTransport({
    service: 'Gmail',
    auth: {
        user: 'bryansagarino222@gmail.com',
        pass: ''
    }
});


exports.sendEmail = (to, subject, htmlContent) => {
    
    let mailOptions = {
        from: 'rybrybb@gmail.com',
        to: to,
        subject: subject,
        html: htmlContent  
    };

    
    transporter.sendMail(mailOptions, (error, info) => {
        if (error) {
            console.log('Error occurred while sending email:', error);
        } else {
            console.log('Email sent:', info.response);
        }
    });
};
